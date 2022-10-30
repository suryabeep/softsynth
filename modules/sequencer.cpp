#include "sequencer.hpp"

#include <map>

namespace ModSynth
{

// The input notes should have the name and duration fields populated.
// This constructor will then cclculate the frequencies
Sequencer::Sequencer(std::vector<Note> &notes) {
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
        if (note.name.compare("-") == 0)
        {
            note.frequency = 0;
        }
        else
        {
            auto octave_pos = note.name.find_first_of("0123456789");
            auto base_note = base_notes.at(note.name.substr(0, octave_pos));
            auto octave = std::stoi(note.name.substr(octave_pos));
            note.frequency  = 440.0f * std::exp2((base_note - 9) / 12.0f + octave - 4);
        }
        
        total_subdivs += note.duration;
    }

    _notes = std::move(notes);
    subdivisionIndex = -1;
    currentNoteStartSubdivision = 0;
    noteIndex = 0;

    index = frequencies.size() - 1;
}

// Update is called for every sample
void Sequencer::update() {
    // move to next subdivision
    if (clock_in > 0 && !gate_out) {
        subdivisionIndex++;

        // move to next note
        if (subdivisionIndex >= currentNoteStartSubdivision + _notes[noteIndex].duration)
        {
            subdivisionIndex %= total_subdivs;
            currentNoteStartSubdivision = subdivisionIndex;
            noteIndex++;
            noteIndex = noteIndex % _notes.size();
        }
    }
    frequency_out = _notes[noteIndex].frequency;
    gate_out = clock_in > 0;
}

};