#ifndef EXOALGO_H
#define EXOALGO_H
class Algorythm
{
public:
	float normalizeBetweenThresholds(float rawInput, float softenTreshold, float hardTreshold);
	float applySinusoidalClip(float inputValue, float scaleFactor, float maxThreshold);
};
#endif
