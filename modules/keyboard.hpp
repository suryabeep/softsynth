#pragma once

#include "../modsynth.h"

namespace ModSynth
{

class Keyboard: public Module {
public:
    bool quit{false};
    float gate_out{};
    float frequency_out{};
    int octave{4};
    Keyboard() = default;
    void update();
};

};
