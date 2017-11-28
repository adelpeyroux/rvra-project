#include "MarkerGraph.hpp"

MarkerGraph::MarkerGraph(std::vector<aruco::Marker> &markers, cv::Size s, double time)
{
    _root = MarkerGraph::Node(xMarker(s.height, s.width), -1, time);
    _size = s;
    _markers.reserve(markers.size());
    vector<int> sources;
    vector<MarkerGraph::Node> effects;
    int index = 0;
    for (aruco::Marker m : markers) {
        xMarker tmp (m);
        if (tmp.IsSource()){
            sources.push_back(index);
        }else
        {
            effects.push_back(Node(tmp, index, time));
        }
        _markers.push_back(tmp);
        index ++;
    }
   // _edges = std::vector<std::pair<int,int>>();

    for (int id : sources){
        MarkerGraph::Node current(_markers[id], id, time);
        MarkerGraph::Node tmp;
        bool find = false;
        do{
            find = FindProximity(current, effects, tmp);
            if (find){
                addEdge(current.GetMarkerIndex(), tmp.GetMarkerIndex());
                tmp.AddInput(current);
                current = tmp;
                find = false;
            }
        }while(find);
        addEdge(current.GetMarkerIndex(), _root.GetMarkerIndex());

        _root.AddInput(current);
    }
}

bool MarkerGraph::FindProximity(MarkerGraph::Node& current, vector<MarkerGraph::Node>& effects, MarkerGraph::Node& tmp){
    cv::Point p = _markers[current.GetMarkerIndex()].GetCenter() - cv::Point(_size.width/2, _size.height/2 );
    float distance = std::min(p.dot(p), PROXIMITY*PROXIMITY);

    Node minNode = current;
    bool find = false;
    for (Node e : effects){
        cv::Point tmp = _markers[minNode.GetMarkerIndex()].GetCenter() - _markers[e.GetMarkerIndex()].GetCenter();
        float d = tmp.dot(tmp);
        if ( d < distance){
            minNode = e;
            find = true;
            distance = d;
        }
    }
    if (find)
        tmp = minNode;
    return find;
}

void MarkerGraph::addEdge (int from, int to){
    _edges.push_back(std::pair<int,int>(from, to));
}

void MarkerGraph::addMarker (aruco::Marker & marker){
    _markers.push_back(marker);
}

void MarkerGraph::addEdges (std::vector<std::pair<int, int>>& edges){
    _edges.insert(_edges.end(), edges.begin(), edges.end());
}

void MarkerGraph::addMarkers (std::vector<aruco::Marker>& markers){
    _markers.insert(_markers.end(), markers.begin(), markers.end());
}

void MarkerGraph::clear(){
    _markers.clear();
    _edges.clear();
}

double MarkerGraph::play(double input, double time) {
    return _root.play_rec(input, time);
}

const std::vector<xMarker> & MarkerGraph::getMarkers() const {
    return _markers;
}

const std::vector<std::pair<int, int>> & MarkerGraph::getEdges() const {

    return _edges;
}

