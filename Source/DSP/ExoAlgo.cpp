#define _USE_MATH_DEFINES

#include "ExoAlgo.h"
#include <cmath>

float ExoAlgo::normalizeBetweenThresholds(float input, float softenThreshold, float hardThreshold) {
    float tresholdDifference;
    float adjustedInput;
    float output;

    tresholdDifference = hardThreshold - softenThreshold;
    adjustedInput = input - softenThreshold;
    output = adjustedInput / tresholdDifference;

    return output;
};

float ExoAlgo::applySinusoidalClip(float inputValue, float scalingFactor, float maxThreshold)
{
    float finalOutput;
    bool isInputNegative = inputValue < 0;
    inputValue = std::abs(inputValue);

    softenThreshold = maxThreshold * scalingFactor;

    if (inputValue >= softenThreshold)
    {

        float thresholdDifference = maxThreshold - softenThreshold;
        float linearValue = normalizeBetweenThresholds(inputValue, softenThreshold, maxThreshold);

        if (linearValue < M_PI / 2)
        {
            float adjustedOutput = sin(linearValue) * thresholdDifference;
            finalOutput = adjustedOutput + softenThreshold;
        }
        else
        {
            finalOutput = maxThreshold;
        }
    }
    else
    {
        finalOutput = inputValue;
    }

    if (isInputNegative)
    {
        finalOutput = -finalOutput;
    }

    return finalOutput;
}