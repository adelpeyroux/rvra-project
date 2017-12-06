#include "AmNode.hpp"
#include "MiscConsts.hpp"

//****************************************
//***** Constructeurs / Destructeurs *****
//****************************************
AmNode::AmNode(int id, double freq, double time)
	: AudioNode(id, time), _freq(freq), _initTime(time), _phi0(PHI[id])
{
	_osc.phaseReset(PHI[_id]);
}

//****************
//***** Play *****
//****************
double AmNode::Play(AudioParams input, double time)
{
	double inVal = 0.;
	double c = 0.;
	GetSignalsAndNumerics(input, inVal, c);

	c /= 32.0;

	const double value = (c + inVal) * _osc.sinewave(_freq);

	IncrPhi(_id, _freq);
	return value;
}
