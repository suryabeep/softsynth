#pragma once

#include "../modsynth.h"

namespace ModSynth
{
    // Note number of 0 indicates a rest
    struct Note
    {
        std::string name;
        int duration{};
        float frequency{};
    };


class Sequencer: public Module {
    // The sequencer takes a clock signal from an external VCO
    // it assumes that this clock signal is being generated at a subdivions = base_subdivision
    // Notes are assigned a length measured in subdivions. 
    // So VCO set to 1 Hz with sub=32, and a note sequence of (C,4), (E, 3), (G, 2) would 
    // play C for 4 seconds, E for 3 seconds, and G for 2 seconds.
    // The sequencer also needs to support rests.

    public:
        // Trigger input
        float clock_in{}; // > 0 triggers next note

        // Parameters
        std::vector<float> frequencies; // Hz
        std::vector<Note> _notes;

        // Output
        float frequency_out; // Hz
        float gate_out;

        // "-" indicates a rest
        Sequencer(std::vector<Note> &notes);
        void update();

    private:
        // Internal state
        std::size_t index;
        int subdivisionIndex{};
        int noteIndex{};
        int currentNoteStartSubdivision{};
        int total_subdivs{};
};

};
