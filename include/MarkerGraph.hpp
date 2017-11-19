#ifndef MARKERGRAPH_H
#define MARKERGRAPH_H

#include <aruco.h>
#include <stdlib.h>

class MarkerGraph
{
private:
    std::vector<aruco::Marker> _markers;
    std::vector<std::pair<int, int>> _edges; // from == first -> to == second

    int findMarker(const aruco::Marker & marker) const;
public:
    MarkerGraph();

    void addEdge (int from, int to);
    void addMarker (aruco::Marker& marker);

    void addEdges (std::vector<std::pair<int, int>>& edges);
    void addMarkers (std::vector<aruco::Marker>& markers);
    void clear();

    const std::vector<aruco::Marker> & getMarkers() const;
    const std::vector<std::pair<int, int>> & getEdges() const;

    const std::vector<aruco::Marker>& getAccessibleMarkersFrom (const aruco::Marker& marker) const;
};

#endif // MARKERGRAPH_H
