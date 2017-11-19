#pragma once

#include <stdlib.h>

#include "AudioNode.hpp"
#include "MarkerGraph.hpp"

class AudioGraph
{
private:
    class Node {
    public :
        Node(){}

        Node (AudioNode* audio) : _audio(audio)
        {
            _outputs = std::vector<Node>();
            _inputs = std::vector<Node>();
        }

    private :
        std::vector<Node> _outputs;
        std::vector<Node> _inputs;

        AudioNode* _audio;


    };

    Node root;

public:
    AudioGraph();

    double * play();

    void update(const MarkerGraph & graph);
};

