#include "../modsynth.h"
#include "vco.hpp"

namespace ModSynth
{
    void VCO::update() {
        frequency = frequency / pow(2, octaveShift);
        float phaseIncrement = frequency * dt;
        if (shape == WaveShape::SINE)
        {
            phaseIncrement *= 2 * (float) M_PI;
        }

        currentPhase += phaseIncrement;
        
        // bring phase back into [0, 2*PI]
		while(currentPhase >= 2 * (float)M_PI)
			currentPhase -= 2 * (float)M_PI;
		while(currentPhase < 0)
			currentPhase += 2 * (float)M_PI;

        if (shape == WaveShape::SAW)
        {
            audio_out = (currentPhase / (2 * (float) M_PI)) * 2.0f - 1.0f;
        }
        else if (shape == WaveShape::SINE)
        {
            audio_out = std::sin(currentPhase);
        }
        else if (shape == WaveShape::SQUARE)
        {
            if (currentPhase < pulseWidth * 2 * (float) M_PI)
            {
                audio_out = 1.0f;
            }
            else{
                audio_out = -1.0f;
            }
        }
        else if (shape == WaveShape::TRIANGLE)
        {
            audio_out = std::abs((currentPhase / (2 * (float) M_PI)) - 0.5f) * 4.0f - 1.0f; 
        }
        else if (shape == WaveShape::NOISE)
        {
		    audio_out = (((float)rand()) / ((float)RAND_MAX) * 2.0f) - 1.0f;
        }
    }
};
