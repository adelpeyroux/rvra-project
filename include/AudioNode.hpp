#pragma once
#include <vector>

class AudioParam
{
public :
	int type;
	double value;

	//***** Constructeurs / Destructeurs *****
	AudioParam(int type, double value)
		: type(type), value(value) {}
	virtual ~AudioParam() = default;
};

class AudioParams
{
private:
	std::vector<AudioParam> _params;

public :
	//***** Constructeurs / Destructeurs *****
	AudioParams() { _params = std::vector<AudioParam>(); }
	virtual ~AudioParams() = default;

	//***** Adds *****
	void AddParam(int type, double value) { _params.push_back(AudioParam(type, value)); }
	void AddParam(AudioParam p) { _params.push_back(p); }
	void AddParams(const AudioParams& params)
	{
		_params.insert(_params.end(), params._params.begin(), params._params.end());
	}

	//***** Getters / Setters *****
	std::vector<float> GetValues(int type)
	{
		std::vector<float> result = std::vector<float>();
		for (AudioParam p : _params) {
			if (p.type == type) {
				result.push_back(p.value);
			}
		}
		return result;
	}

	std::vector<AudioParam> GetParams() const { return _params; }
};


class AudioNode
{
protected:
	int _id;
	double _phi;
public:
	//***** Constructeurs / Destructeurs *****
	AudioNode(int id, double time)
		: _id(id), _phi(0) {}
	virtual ~AudioNode() = default;

	//***** Play *****
	virtual double Play(AudioParams input, double time) = 0;
};
