#include "DestinationNode.hpp"
#include "MiscConsts.hpp"

//****************************************
//***** Constructeurs / Destructeurs *****
//****************************************
DestinationNode::DestinationNode(int id, double time)
	: AudioNode(id, time) {}

//****************
//***** Play *****
//****************
double DestinationNode::Play(AudioParams input, double time)
{
	double inVal = 0.;
	int nbVal = 0;

	for (uint i = 0; i < input.GetParams().size(); ++i) {
		if (input.GetParams()[i].type != TYPE_SOURCE_NUMERICAL) {
			inVal += input.GetParams()[i].value;
			nbVal ++;
		}
	}

	if (nbVal > 0) return inVal / nbVal;


	return 0.;
}
