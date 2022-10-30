#include "modsynth.h"
#include "modules/vco.hpp"
#include "modules/vcf.hpp"
#include "modules/envelope.hpp"
#include "modules/delay.hpp"
#include "modules/sequencer.hpp"
#include "modules/keyboard.hpp"
#include "modules/mixer.hpp"

#include <iostream>

using namespace ModSynth;

// This project used the code at https://codereview.stackexchange.com/questions/254421/modular-synthesizer-framework-for-c
// as a starting point. I have since incorporated some of the things at https://blog.demofox.org/diy-synthesizer/
// and implemented some additional features of my own.
// The intention of this code is to eventually be used as an augmentation for my hardware synth setup at home.
// I don't really care about a GUI at the moment as I will most likely be using MIDI I/O as required.

int main() {
    // Keyboard control
    Keyboard keys;

    // Sequencer unit
    VCO clock{250}; // BPM input
    std::vector<Note> notes = {
        {std::string("C5"), 3, 0},
        {std::string("E5"), 2, 0},
        {std::string("G5"), 2, 0},
        {std::string("-"), 1, 0},
        {std::string("B5"), 3, 0},
    };
    Sequencer sequencer{notes};

    // Voice 1
    VCO vco1{WaveShape::SAW};
    VCF vcf1{0.1, 0.9, LOWPASS, FOUR_POLE};
    VCA vca1{2000};

    // Voice 2
    VCO vco2{WaveShape::SAW};
    VCF vcf2{0.1, 0.5, LOWPASS, FOUR_POLE};
    VCA vca2{2000};
    vco2.octaveShift = -1;

    // Envelopes
    Envelope envelope{0.1, 0.2, 0.2};

    // Effects
    Delay delay{0.5f, 0.5f, DelayMode::STANDARD};

    // Output
    Mixer mixer({1.0f, 1.0f});
    Speaker speaker;

    // Two voice sequencer with effects
    Wire wires[]{
        {sequencer.clock_in,  clock.audio_out},
        {envelope.gate_in,    sequencer.gate_out},
        // Voice 1 wiring
        {vco1.frequency,      sequencer.frequency_out},
        {vcf1.audio_in,       vco1.audio_out},
        {vcf1.contour,        envelope.amplitude_out},
        {vca1.audio_in,       vcf1.audio_out},
        {vca1.amplitude,      envelope.amplitude_out},
        // Voice 2 wiring
        {vco2.frequency,      sequencer.frequency_out},
        {vcf2.audio_in,       vco2.audio_out},
        {vcf2.contour,        envelope.amplitude_out},
        {vca2.audio_in,       vcf2.audio_out},
        {vca2.amplitude,      envelope.amplitude_out},
        // Output section wiring
        {mixer.audio_ins[0], vca1.audio_out},
        {mixer.audio_ins[1], vca2.audio_out},
        {speaker.left_in,    mixer.audio_out},
        {speaker.right_in,   mixer.audio_out},

        // only Voice 1
        // {speaker.left_in,    vca1.audio_out},
        // {speaker.right_in,   vca1.audio_out},
    };

    fprintf(stderr, "Press q to quit\n");

    while(!keys.quit);

    SDL_Quit();

    return 0;
}