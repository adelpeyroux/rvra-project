#ifndef MARKERGRAPH_H
#define MARKERGRAPH_H

#include <aruco.h>
#include <stdlib.h>
#include "xMarker.hpp"
#include "AudioNode.hpp"

class MarkerGraph
{

private :
    class Node {
    public :
        Node(){}

        Node (const xMarker& marker, int index)
        {
            _markerIndex = index;
        }
        void AddInput(Node &node){
            _inputs.push_back(node);
        }

    int GetMarkerIndex(){
        return _markerIndex;
    }

    private :
        std::vector<Node> _inputs;

        AudioNode* _audio;
        int _markerIndex;

    };

    std::vector<xMarker> _markers;
    std::vector<std::pair<int, int>> _edges; // from == first -> to == second
    Node _root;

    int findMarker(const xMarker & marker) const;
public:
    MarkerGraph(){}
    MarkerGraph(std::vector<aruco::Marker> &markers, cv::Size s);

    void addEdge (int from, int to);
    void addMarker (aruco::Marker& marker);

    void addEdges (std::vector<std::pair<int, int>>& edges);
    void addMarkers (std::vector<aruco::Marker>& markers);
    void clear();

    const std::vector<xMarker> & getMarkers() const;
    const std::vector<std::pair<int, int>> & getEdges() const;

    const std::vector<aruco::Marker>& getAccessibleMarkersFrom (const xMarker& marker) const;
    bool FindProximity(Node& current, std::vector<Node>& effect, MarkerGraph::Node& tmp);
    cv::Size _size;


};

#endif // MARKERGRAPH_H
