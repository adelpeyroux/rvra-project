#pragma once

#include "AudioNode.hpp"
#include "maximilian.h"

class AmNode : public AudioNode
{
private :
	maxiOsc _osc;
	double _freq;
	double _initTime;
	double _phi0;

public:
	//***** Constructeurs / Destructeurs *****
	AmNode(int id, double freq, double time);
	virtual ~AmNode() = default;

	//***** Play *****
	double Play(AudioParams input, double time) override;
};
