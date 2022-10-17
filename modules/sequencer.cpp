#include "sequencer.hpp"

#include <map>

namespace ModSynth
{

Sequencer::Sequencer(std::initializer_list<std::string> notes) {
    static const std::map<std::string, int> base_notes = {
        {"Cb", -1}, {"C", 0}, {"C#", 1},
        {"Db", 1}, {"D", 2}, {"D#", 3},
        {"Eb", 3}, {"E", 4}, {"E#", 5},
        {"Fb", 4}, {"F", 5}, {"F#", 6},
        {"Gb", 6}, {"G", 7}, {"G#", 8},
        {"Ab", 8}, {"A", 9}, {"A#", 10},
        {"Bb", 10}, {"B", 11}, {"B#", 12},
    };

    for (auto &note: notes) {
        auto octave_pos = note.find_first_of("0123456789");
        auto base_note = base_notes.at(note.substr(0, octave_pos));
        auto octave = std::stoi(note.substr(octave_pos));
        frequencies.push_back(440.0f * std::exp2((base_note - 9) / 12.0f + octave - 4));
    }

    index = frequencies.size() - 1;
}

void Sequencer::update() {
    if (clock_in > 0 && !gate_out) {
        index++;
        index %= frequencies.size();
    }

    frequency_out = frequencies[index];
    gate_out = clock_in > 0;
}

};