#pragma once

#include "../modsynth.h"

#include <vector>

namespace ModSynth
{

class Mixer: public Module {
    public:
        std::vector<float> audio_ins;
        std::vector<float> weights;
        float audio_out{};

        // Audio output
        Mixer() = default;
        Mixer(std::initializer_list<float> weightsIn);
        void update();
};

};
