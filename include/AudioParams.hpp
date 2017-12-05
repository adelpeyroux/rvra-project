#ifndef __AUDIO_PARAMS_HPP__
#define __AUDIO_PARAMS_HPP__

#include "MiscConsts.hpp"
#include <stdlib.h>

class AudioParams {
public :
    AudioParams ();
    void AddParam (int type, float value);

    void AddParams (const AudioParams & params) ;

    std::vector<float> GetValues (int type);

    std::vector< std::pair<int, float> > GetParams();



private :

    std::vector<std::pair<int, float>> _params;
};

#endif __AUDIO_PARAMS_HPP__
