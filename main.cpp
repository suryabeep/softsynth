#include "modsynth.h"
#include "modules/vco.hpp"
#include "modules/vcf.hpp"
#include "modules/envelope.hpp"
#include "modules/delay.hpp"
#include "modules/sequencer.hpp"
#include "modules/keyboard.hpp"
#include "modules/mixer.hpp"
#include "midiInput.h"

#include <iostream>

using namespace ModSynth;

int main() {
    // Initialize Midi control
    MidiInput midiIn;
    
    // Keyboard control
    Keyboard keys;


    // Sequencer unit
    VCO clock{250}; // BPM input
    std::vector<Note> notes = {
        {std::string("C4"), 3, 0},
        {std::string("E4"), 2, 0},
        {std::string("G4"), 2, 0},
        {std::string("-"), 1, 0},
        {std::string("B4"), 3, 0},
    };
    Sequencer sequencer{notes};

    // Voice 1
    VCO vco1{WaveShape::SAW};
    VCF vcf1{0.1, 0.9, LOWPASS, FOUR_POLE};
    VCA vca1{2000};

    // Voice 2
    VCO vco2{WaveShape::SINE};
    VCF vcf2{0.1, 0.5, LOWPASS, FOUR_POLE};
    VCA vca2{2000};
    vco2.octaveShift = -1;

    // Envelopes
    Envelope envelope1{0.1, 0.2, 0.2};
    Envelope envelope2{0.1, 0.5, 0.5};

    // Effects
    Delay delay{0.5f, 0.5f, DelayMode::STANDARD};

    // Output
    Mixer mixer({1.0f, 0.5f});
    Speaker speaker;

    // Two voice sequencer with effects
    Wire wires[]{
        {sequencer.clock_in,  clock.audio_out},

        // Voice 1 wiring
        {envelope1.gate_in,   keys.gate_out},
        {vco1.frequency,      keys.frequency_out},
        {vcf1.audio_in,       vco1.audio_out},
        {vcf1.contour,        envelope1.amplitude_out},
        {vca1.audio_in,       vcf1.audio_out},
        {vca1.amplitude,      envelope1.amplitude_out},
        // Voice 2 wiring
        {envelope2.gate_in,   sequencer.gate_out},
        {vco2.frequency,      sequencer.frequency_out},
        {vcf2.audio_in,       vco2.audio_out},
        {vcf2.contour,        envelope2.amplitude_out},
        {vca2.audio_in,       vcf2.audio_out},
        {vca2.amplitude,      envelope2.amplitude_out},
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