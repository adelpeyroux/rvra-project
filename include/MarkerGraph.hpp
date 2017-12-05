#ifndef MARKERGRAPH_H
#define MARKERGRAPH_H

#include <aruco.h>
#include <stdlib.h>
#include "xMarker.hpp"
#include "AudioNode.hpp"
#include "AudioParams.hpp"

class MarkerGraph
{

private :
    class Node {
    public :
        Node(){
            _markerIndex = -2;
            _inputs = std::vector<Node>();
        }

        Node (const xMarker& marker, int index, double time)
        {
            _inputs = std::vector<Node>();
            _markerIndex = index;
            _audio = getAudioNode( marker.GetType(), marker.GetAngle(), time, marker.GetMarker().id);
            _type = marker.GetType();
        }
        void AddInput(Node &node){
            _inputs.push_back(node);
        }

        int GetMarkerIndex(){
            return _markerIndex;
        }

        AudioParams play_rec (AudioParams sample, double time) {

            AudioParams inputParams = AudioParams();
            if (_inputs.size() > 0) {
                for (int i = 0; i < _inputs.size(); ++i) {
                    AudioParams p = _inputs[i].play_rec(sample, time);
                    inputParams.AddParams(p);
                }
            }

            float value =  _audio->play(inputParams, time);
            MARKER_TYPE type = _type;

            AudioParams result = AudioParams();
            result.AddParam(type, value);

            return result;
        }

        void save_phi(){

        }

    private :
        std::vector<Node> _inputs;

        AudioNode* _audio;
        int _markerIndex;
        MARKER_TYPE _type;
    };

    std::vector<xMarker> _markers;
    std::vector<std::pair<int, int>> _edges; // from == first -> to == second
    Node _root;

    int findMarker(const xMarker & marker) const;
public:
    MarkerGraph(){}
    MarkerGraph(std::vector<aruco::Marker> &markers, cv::Size s, double time);

    void addEdge (int from, int to);
    void addMarker (aruco::Marker& marker);

    void addEdges (std::vector<std::pair<int, int>>& edges);
    void addMarkers (std::vector<aruco::Marker>& markers);
    void clear();

    double play(double, double);

    const std::vector<xMarker> & getMarkers() const;
    const std::vector<std::pair<int, int>> & getEdges() const;

    const std::vector<aruco::Marker>& getAccessibleMarkersFrom (const xMarker& marker) const;
    bool FindProximity(Node& current, std::vector<Node>& effect, MarkerGraph::Node& tmp);
    cv::Size _size;


};

#endif // MARKERGRAPH_H
