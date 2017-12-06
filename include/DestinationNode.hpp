#pragma once

#include "AudioNode.hpp"

class DestinationNode : public AudioNode
{
public:
	//***** Constructeurs / Destructeurs *****
	DestinationNode(int id, double time);
	virtual ~DestinationNode() = default;

	//***** Play *****
	double Play(AudioParams input, double time) override;
};
