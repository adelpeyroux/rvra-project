#pragma once

#include "AudioNode.hpp"
#include "MarkerGraph.hpp"

class AudioGraph
{
private:
	class Node
	{
	private:
		vector<Node> _inputs, _outputs;
		AudioNode* _audio;

	public :
		//***** Constructeurs / Destructeurs *****
		Node() : _audio(nullptr) {}

		explicit Node(AudioNode* audio) : _audio(audio)
		{
			_outputs = std::vector<Node>();
			_inputs = std::vector<Node>();
		}
		virtual ~Node() = default;
	};

	Node root;

public:
	//***** Constructeurs / Destructeurs *****
	AudioGraph() {}
	virtual ~AudioGraph() = default;

	//***** Misc *****
	double* Play();
	void Update(const MarkerGraph& graph);
};
