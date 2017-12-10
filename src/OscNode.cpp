#include "OscNode.hpp"
#include "MiscConsts.hpp"

//****************************************
//***** Constructeurs / Destructeurs *****
//****************************************
OscNode::OscNode(int id, double freq, int type, double time)
	: AudioNode(id, time), _freq(freq), _initTime(time), _phi0(PHI[id]), _type(type)
{
	_osc.phaseReset(PHI[_id]);
}

//****************
//***** Play *****
//****************
double OscNode::Play(AudioParams input, double time)
{
	double value;

	switch (_type) {
	case OSC_SAW:				value = _osc.sawn(_freq);		break;
	case OSC_SQUARE:			value = _osc.square(_freq);		break;
	case OSC_TRIANGLE:			value = _osc.triangle(_freq);	break;
	case OSC_SINE:	default:	value = _osc.sinewave(_freq);	break;
	}


	IncrPhi(_id, _freq);
	return value;
}
