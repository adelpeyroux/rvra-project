#pragma once

#include "AudioNode.hpp"

class NumericalNode : public AudioNode
{
private:
	double _value;

public:
	//***** Constructeurs / Destructeurs *****
	NumericalNode(int id, double value, double time);
	virtual ~NumericalNode() = default;

	//***** Play *****
	double Play(AudioParams input, double time) override;
};
