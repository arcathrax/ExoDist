#define _USE_MATH_DEFINES

#include "ExoAlgo.h"
#include <cmath>

float Algorythm::normalizeBetweenThresholds(float input, float softenTreshold, float hardTreshold) {
    float tresholdDifference;
    float adjustedInput;
    float output;

    tresholdDifference = hardTreshold - softenTreshold;
    adjustedInput = input - softenTreshold;
    output = adjustedInput / tresholdDifference;

    return output;
};

float Algorythm::applySinusoidalClip(float inputValue, float scalingFactor, float maxThreshold)
{
    float finalOutput;
    bool isInputNegative = inputValue < 0;
    inputValue = std::abs(inputValue);

    scalingFactor = maxThreshold * scalingFactor;

    if (inputValue >= scalingFactor)
    {

        float thresholdDifference = maxThreshold - scalingFactor;
        float linearValue = normalizeBetweenThresholds(inputValue, scalingFactor, maxThreshold);

        if (linearValue < M_PI / 2)
        {
            float adjustedOutput = sin(linearValue) * thresholdDifference;
            finalOutput = adjustedOutput + scalingFactor;
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