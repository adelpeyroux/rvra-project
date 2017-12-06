#pragma once

#include "AudioNode.hpp"
#include "maximilian.h"

#define OSC_SINE 0
#define OSC_SAW 1
#define OSC_TRIANGLE 2
#define OSC_SQUARE 3

class OscNode : public AudioNode
{
private:
	maxiOsc _osc;
	double _freq;
	double _initTime;
	double _phi0;
	int _type;

public:
	//***** Constructeurs / Destructeurs *****
	OscNode(int id, double freq, int type, double time);
	virtual ~OscNode() = default;

	//***** Play *****
	double Play(AudioParams input, double time) override;
};
