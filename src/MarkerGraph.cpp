#include "MarkerGraph.hpp"

MarkerGraph::MarkerGraph()
{
    _markers = std::vector<aruco::Marker>();
    _edges = std::vector<std::pair<int,int>>();
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

const std::vector<aruco::Marker> & MarkerGraph::getMarkers() const {
    return _markers;
}

const std::vector<std::pair<int, int>> & MarkerGraph::getEdges() const {
    return _edges;
}

int MarkerGraph::findMarker(const aruco::Marker& marker) const {
    int index = 0;

    for (index = 0; index < _markers.size(); ++index){
        if (_markers[index] == marker) {
            return index;
        }
    }
}

const std::vector<aruco::Marker>& MarkerGraph::getAccessibleMarkersFrom (const aruco::Marker& marker) const {
    int index = findMarker(marker);

    std::vector<aruco::Marker> result = std::vector<aruco::Marker>();

    for (std::pair<int, int> p : _edges) {
        if (p.first == index) {
            result.push_back(_markers[p.second]);
        }
    }
    return result;
}
