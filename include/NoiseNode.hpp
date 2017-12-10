#pragma once

#include "AudioNode.hpp"

class NoiseNode : public AudioNode
{
private:
	double _samples;

public:
	//***** Constructeurs / Destructeurs *****
	NoiseNode(int id, double samples, double time);
	virtual ~NoiseNode() = default;

	//***** Play *****
	double Play(AudioParams input, double time) override;
};
