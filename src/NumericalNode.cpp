#include "NumericalNode.hpp"

//****************************************
//***** Constructeurs / Destructeurs *****
//****************************************
NumericalNode::NumericalNode(int id, double value, double time)
	: AudioNode(id, time), _value(value) {}

//****************
//***** Play *****
//****************
double NumericalNode::Play(AudioParams input, double time)
{
	return _value;
}
