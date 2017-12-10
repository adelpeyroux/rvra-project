#include "MarkerGraph.hpp"

using namespace std;
using namespace cv;

//****************************************
//***** Constructeurs / Destructeurs *****
//****************************************
MarkerGraph::MarkerGraph(vector<aruco::Marker>& markers, Size s, double time)
{
	_root = Node(xMarker(s.height, s.width), -1, time);
	_Size = s;
	_markers.reserve(markers.size());
	vector<int> sources;
	vector<Node> effects;
	int index = 0;
	for (const aruco::Marker& m : markers) {
		xMarker tmp(m);
		if (tmp.isSource()) {
			sources.push_back(index);
		} else {
			effects.push_back(Node(tmp, index, time));
		}
		_markers.push_back(tmp);
		index ++;
	}

	for (int id : sources) {
		Node current(_markers[id], id, time);
		Node tmp;
		bool find;
		do {
			find = FindProximity(current, effects, tmp);
			if (find) {
				AddEdge(current.GetMarkerIndex(), tmp.GetMarkerIndex());
				tmp.AddInput(current);
				current = tmp;
				find = false;
			}
		} while (find);
		AddEdge(current.GetMarkerIndex(), _root.GetMarkerIndex());

		_root.AddInput(current);
	}
}

void MarkerGraph::DeleteRec(Node& current)
{
	if (current.get_audio_node() != nullptr) {
		if (current.get_input().size() > 0) {
			for (uint i = 0; i < current.get_input().size(); ++i) {
				DeleteRec(current.get_input()[i]);
			}
		}

		current.remove();
	}
}

MarkerGraph::~MarkerGraph()
{
	DeleteRec(_root);
}

//************************
//***** Adds / Clear *****
//************************
void MarkerGraph::AddEdge(int from, int to)
{
	_edges.push_back(pair<int, int>(from, to));
}

void MarkerGraph::AddMarker(aruco::Marker& marker)
{
	_markers.push_back(xMarker(marker));
}


void MarkerGraph::Clear()
{
	_markers.clear();
	_edges.clear();
}



//******************
//***** Getter *****
//******************
const vector<xMarker>& MarkerGraph::GetMarkers() const
{
	return _markers;
}

const vector<pair<int, int>>& MarkerGraph::GetEdges() const
{
	return _edges;
}

//****************
//***** Play *****
//****************
double MarkerGraph::Play(double input, double time)
{
	const AudioParam root = _root.play_rec(AudioParams(), time);
	return root.value;
}

bool MarkerGraph::FindProximity(Node& current, vector<Node>& effects, Node& tmp)
{
	Point p = _markers[current.GetMarkerIndex()].GetCenter() - Point(_Size.width / 2, _Size.height / 2);
	float distance = min(p.dot(p), PROXIMITY*PROXIMITY);

	Node minNode = current;
	bool find = false;
	for (Node e : effects) {
		Point tmp_p = _markers[minNode.GetMarkerIndex()].GetCenter() - _markers[e.GetMarkerIndex()].GetCenter();
		const float d = tmp_p.dot(tmp_p);
		if (d < distance) {
			minNode = e;
			find = true;
			distance = d;
		}
	}
	if (find) tmp = minNode;
	return find;
}
