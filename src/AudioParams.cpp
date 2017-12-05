#include "AudioParams.hpp"

AudioParams::AudioParams () {
    _params = std::vector<std::Pair<MARKER_TYPE, float>>();
}

void AudioParams::AddParam (MARKER_TYPE type, float value){
    _params.push_back(std::make_pair(type, value));
}

void AudioParams::AddParams (const AudioParams & params) {
    _params.insert(_params.end(), params.begin(), params.end());
}

std::vector<float> AudioParams::GetValues (MARKER_TYPE type) {
    std::vector<float> result();
    for (auto p : _params) {
        if (p.first == type) {
            resul.push_back(p.second);
        }
    }
    return result;
}

const std::vector<std::Pair<MARKER_TYPE, float>> & AudioParams::GetParams() {
    return _params;
}
