#define _USE_MATH_DEFINES

#include "ExoAlgo.h"
#include <cmath>


float ExoAlgo::getLinearValue(float input, float sct, float hct)
{
    tDiff = hct - sct;
    adjInput = input - sct;
    output = adjInput / tDiff;
    return output;
}

float ExoAlgo::sinClip(float input, float sct, float hct)
{
    bool isNegative = input < 0;
    input = std::abs(input);

    sct = hct * sct;

    if (input >= sct)
    {
        tDiff = hct - sct;
        linearOutput = getLinearValue(input, sct, hct);

        if (linearOutput < M_PI / 2)
        {
            adjOutput = sin(linearOutput) * tDiff;
            realOutput = adjOutput + sct;
        }
        else
        {
            realOutput = hct;
        }
    }
    else
    {
        realOutput = input;
    }

    // Spiegelung für negative Eingabewerte
    if (isNegative)
    {
        realOutput = -realOutput;
    }

    return realOutput;
}

float ExoAlgo::softWeird(float input, float d)
{
    float a = (sin(input) / 2) * d;

    return atan(input * d * pow(a, 2));
}

float ExoAlgo::hardWerid(float input, float d)
{
    float a = (sin(input) / 2) * d;

    return tanh(input * 4 * d * pow(a,2));
}