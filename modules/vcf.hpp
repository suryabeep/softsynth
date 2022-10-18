#pragma once

#include "../modsynth.h"

namespace ModSynth
{

enum FilterMode
{
    LOWPASS,
    HIGHPASS,
    BANDPASS
};

enum FilterType
{
    FOUR_POLE,
    TWO_POLE,
};

class VCF: public Module {
    public:
        // Audio input
        float audio_in{};

        // Parameters
        float cutoff{0.99f};    // dimensionless, 0-1
        float resonance{0.0f};  // dimensionless, 0-1
        float contour{0.0f};    // dimensionless, 0-1
        FilterMode mode{FilterMode::LOWPASS};
        FilterType type{FilterType::FOUR_POLE};

        // Audio output
        VCF() = default;
        VCF(float cutoff, float resonance)
            : cutoff(cutoff), resonance(resonance) {}
        VCF(float cutoff, float resonance, FilterMode modeIn)
            : cutoff(cutoff), resonance(resonance), mode(modeIn) {}
        VCF(float cutoff, float resonance, FilterMode modeIn, FilterType typeIn)
            : cutoff(cutoff), resonance(resonance), mode(modeIn), type(typeIn) {}
        void update();

        float buf0{};
        float buf1{};
        float audio_out{};
};

};
