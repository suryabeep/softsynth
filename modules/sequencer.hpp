#pragma once

#include "../modsynth.h"

namespace ModSynth
{

class Sequencer: public Module {
    public:
        // Trigger input
        float clock_in{}; // > 0 triggers next note

        // Parameters
        std::vector<float> frequencies; // Hz

        // Output
        float frequency_out; // Hz
        float gate_out;

        Sequencer(std::initializer_list<std::string> notes);
        void update();

    private:
        // Internal state
        std::size_t index;
};

};
