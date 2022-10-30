#pragma once

#include "../modsynth.h"

namespace ModSynth
{

enum WaveShape
{
    SINE,
    SQUARE,
    SAW,
    TRIANGLE,
    NOISE,
};

class VCO: public Module 
{
    public:
        float frequency{}; // Hz
        WaveShape shape{};
        float audio_out{};
        float currentPhase{};   // should be between 0 and 2*PI.
        float pulseWidth{};
        float octaveShift{0};   // octaves up or down from the fundamental frequency

        VCO() = default;
        VCO(int bpm);
        VCO(float frequencyIn, WaveShape shapeIn, float pulseWidthIn)
            : frequency(frequencyIn), shape(shapeIn), pulseWidth(pulseWidthIn) {};
        VCO(WaveShape shapeIn, float pulseWidthIn)
            : shape(shapeIn), pulseWidth(pulseWidthIn) {};
        VCO(float frequencyIn)
            : frequency(frequencyIn), shape(WaveShape::SQUARE), pulseWidth(0.5f) {};
        VCO(WaveShape shapeIn)
            : shape(shapeIn), pulseWidth(0.5f) {};
        void update();
};

};


