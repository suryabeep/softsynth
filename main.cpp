#include "modsynth.h"
#include "modules/vco.hpp"
#include "modules/vcf.hpp"
#include "modules/envelope.hpp"
#include "modules/delay.hpp"
#include "modules/sequencer.hpp"
#include "modules/keyboard.hpp"

#include <iostream>

using namespace ModSynth;

// This project used the code at https://codereview.stackexchange.com/questions/254421/modular-synthesizer-framework-for-c
// as a starting point. I have since incorporated some of the things at https://blog.demofox.org/diy-synthesizer/
// and implemented some additional features of my own.
// The intention of this code is to eventually be used as an augmentation for my hardware synth setup at home.
// I don't really care about a GUI at the moment as I will most likely be using MIDI I/O as required.

int main() {
    // clock oscillator does not take an input frequency from another module
    VCO clock{1};
    Sequencer sequencer{
        "C4", "E4", "G4", "C5",
    };
    VCO vco{WaveShape::SAW};
    VCF vcf{0.1, 0.5, LOWPASS, TWO_POLE};
    VCA vca{2000};
    Envelope envelope{1, 0.1, 0.1};
    Speaker speaker;
    Keyboard keys;
    Delay delay{0.5f, 0.5f, DelayMode::PING_PONG};

    // Routing signals using Wire objects
    Wire wires[]{
        {envelope.gate_in,   keys.gate_out},
        {vco.frequency,      keys.frequency_out},
        {vcf.audio_in,       vco.audio_out},
        {vcf.contour,        envelope.amplitude_out},
        {vca.audio_in,       vcf.audio_out},
        {vca.amplitude,      envelope.amplitude_out},
        // {delay.audio_in,     vca.audio_out},
        {speaker.left_in,    vcf.audio_out},
        {speaker.right_in,   vcf.audio_out},
    };

    fprintf(stderr, "Press q to quit\n");

    while(!keys.quit);

    SDL_Quit();

    return 0;
}