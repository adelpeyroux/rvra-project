#include "FmNode.hpp"
#include "MiscConsts.hpp"

//****************************************
//***** Constructeurs / Destructeurs *****
//****************************************
FmNode::FmNode(int id, double freq, double time)
	: AudioNode(id, time), _freq(freq), _initTime(time), _phi0(PHI[id])
{
	_osc.phaseReset(PHI[_id]);
}

//****************
//***** Play *****
//****************
double FmNode::Play(AudioParams input, double time)
{
	double inVal = 0.;
    double c = 0.;
	GetSignalsAndNumerics(input, inVal, c);

    const double value = _osc.sinewave(_freq + 100 * inVal);

	IncrPhi(_id, _freq);
	return value;
}
