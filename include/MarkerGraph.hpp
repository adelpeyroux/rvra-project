#pragma once

#include "xMarker.hpp"
#include "AudioNode.hpp"
#include <memory>

class MarkerGraph
{
private :
	class Node
	{
	private:
		vector<Node> _inputs;
		shared_ptr<AudioNode> _audio;
		int _markerIndex;
		MARKER_TYPE _type;

	public :
		//***** Constructeurs / Destructeurs *****
		Node()
			: _type(NO_TYPE)
		{
			_markerIndex = -2;
			_inputs = std::vector<Node>();
			_audio = nullptr;
		}

		Node(const xMarker& marker, int index, double time)
		{
			_inputs = std::vector<Node>();
			_markerIndex = index;
			_audio = GetAudioNode(marker.GetType(), marker.GetAngle(), time, marker.GetMarker().id);
			_type = marker.GetType();
		}
		virtual ~Node() = default;

		void remove() { _audio = nullptr; }

		//***** Getters / Setters *****
		void AddInput(Node& node) { _inputs.push_back(node); }
		int GetMarkerIndex() const { return _markerIndex; }
		vector<Node>& get_input() { return _inputs; }
		shared_ptr<AudioNode> get_audio_node() const { return _audio; }
		void set_audio_node(shared_ptr<AudioNode> a) { _audio = a; }
		
		//***** Play *****
		AudioParam play_rec(AudioParams sample, double time)
		{
			AudioParams inputParams = AudioParams();
			if (_inputs.size() > 0) {
				for (uint i = 0; i < _inputs.size(); ++i) {
					const AudioParam p = _inputs[i].play_rec(sample, time);
					inputParams.AddParam(p);
				}
			}

			const float value = _audio->Play(inputParams, time);
			const MARKER_TYPE type = _type;

			const AudioParam result = AudioParam(type, value);
			return result;
		}
	};

	vector<xMarker> _markers;
	vector<pair<int, int>> _edges; // from == first -> to == second
	Node _root;

public:
	cv::Size _Size;
	//***** Constructeurs / Destructeurs *****
	MarkerGraph() {}
	MarkerGraph(vector<aruco::Marker>& markers, cv::Size s, double time);
	virtual ~MarkerGraph();
	static void DeleteRec(Node& current);

	//***** Adds / Clear *****
	void AddEdge(int from, int to);
	void AddMarker(aruco::Marker& marker);
	void AddEdges(vector<pair<int, int>>& edges);
	void AddMarkers(vector<aruco::Marker>& markers);
	void Clear();

	//***** Getter *****
	const vector<xMarker>& GetMarkers() const;
	const vector<pair<int, int>>& GetEdges() const;

	//***** Play *****
	double Play(double, double);
	
	//***** Misc *****
	bool FindProximity(Node& current, vector<Node>& effect, Node& tmp);
};
