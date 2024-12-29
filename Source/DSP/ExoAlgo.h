#ifndef EXOALGO_H
#define EXOALGO_H

#include <vector>

class ExoAlgo {
public:
    float getLinearValue(float input, float sct, float hct);
    float sinClip(float input, float sct, float hct);
    float softWeird(float input, float d);
    float hardWerid(float input, float d);
private:
    // getLinearValue Variables
    float tDiff;
    float adjInput;
    float output;

    // algorythm Variables
    float linearOutput;
    float adjOutput;
    float realOutput;
};

#endif
