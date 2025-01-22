#ifndef EXOALGO_H
#define EXOALGO_H
class ExoAlgo
{
public:
	// variables

	//functions
	float process(float inputValue);
	
	void setScaleFactor(float newScaleFactor);
	void setMaxThreshold(float newMaxThreshold);
private:
	// variables
	float scaleFactor;
	float maxThreshold;
	float softenThreshold;

	// functions
	float normalizeBetweenThresholds(float rawInput, float softenTreshold, float hardTreshold);
};
#endif
