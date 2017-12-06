#pragma once

#include <stdlib.h>

#include "opencv2/opencv.hpp"

class AudioParam {
public :
    int type;
    float value;

    AudioParam( int type, double value) :
        type(type), value(value)
    {}
};

class AudioParams {
public :
    AudioParams () {
        _params = std::vector<AudioParam>();
    }

    void AddParam (int type, double value) {
        _params.push_back(AudioParam(type, value));
    }

    void AddParam(AudioParam p) {
        _params.push_back(p);
    }

    void AddParams (const AudioParams & params) {
        _params.insert(_params.end(), params._params.begin(), params._params.end());
    }

    std::vector<float> GetValues (int type) {
        std::vector<float> result = std::vector<float>();
        for (AudioParam p : _params) {
            if (p.type == type) {
                result.push_back(p.value);
            }
        }
        return result;
    }

    std::vector< AudioParam > GetParams() {
        return _params;
    }

private :

    std::vector<AudioParam> _params;
};


class AudioNode
{    
protected:
    double _phi;
    int _id;
public:
    AudioNode(int id, double time);
    virtual double play (AudioParams input, double time) = 0;
    virtual ~AudioNode() = default;
};

