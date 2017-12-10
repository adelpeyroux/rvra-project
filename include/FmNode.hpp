#pragma once

#include "AudioNode.hpp"
#include "maximilian.h"

class FmNode : public AudioNode
{
private :
	maxiOsc _osc;
	double _freq;
	double _initTime;
	double _phi0;

public:
	//***** Constructeurs / Destructeurs *****
	FmNode(int id, double freq, double time);
	virtual ~FmNode() = default;

	//***** Play *****
	double Play(AudioParams input, double time) override;
};
