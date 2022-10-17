#pragma once

#include "../modsynth.h"

namespace ModSynth
{

class VCF: public Module {
    public:
        // Audio input
        float audio_in{};

        // Parameters
        float cutoff{}; // Hz
        float resonance{}; // dimensionless,
        float envelope{};

        // Audio output
        float lowpass_out{};
        float bandpass_out{};
        float highpass_out{};

        VCF() = default;
        VCF(float cutoff, float resonance): cutoff(cutoff), resonance(resonance) {}
        void update();
};

};
