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
    // clock oscillator does not take an input frequency from another module
    VCO clock{1};
    Sequencer sequencer{
        "C4", "E4", "G4", "C5",
    };
    VCO vco1{WaveShape::SAW};
    VCO vco2{WaveShape::SAW};
    vco2.octaveShift = log2(1.5);
    Mixer mixer;
    mixer.audio_ins = std::vector<float> {0.5, 0.5};
    mixer.weights = std::vector<float> {0.5, 0.5};

    VCF vcf1{0.1, 0.5, LOWPASS, FOUR_POLE};
    VCF vcf2{0.1, 0.5, LOWPASS, FOUR_POLE};
    VCA vca1{2000};
    VCA vca2{2000};
    Envelope envelope{0.1, 1, 1};
    Speaker speaker;
    Keyboard keys;
    Delay delay{0.5f, 0.5f, DelayMode::PING_PONG};

    // Routing signals using Wire objects
    Wire wires[]{
        {envelope.gate_in,   keys.gate_out},
        {vco1.frequency,      keys.frequency_out},
        {vco2.frequency,      keys.frequency_out},
        {vcf1.audio_in,       vco1.audio_out},
        {vcf2.audio_in,       vco2.audio_out},
        {vcf1.contour,        envelope.amplitude_out},
        {vcf2.contour,        envelope.amplitude_out},
        {vca1.audio_in,       vcf1.audio_out},
        {vca2.audio_in,       vcf2.audio_out},
        {vca1.amplitude,      envelope.amplitude_out},
        {vca2.amplitude,      envelope.amplitude_out},
        // {delay.audio_in,     vca.audio_out},
        // {speaker.left_in,    vcf.audio_out},
        // {speaker.right_in,   vcf.audio_out},
        {mixer.audio_ins[0], vca1.audio_out},
        {mixer.audio_ins[1], vca2.audio_out},
        {speaker.left_in,    mixer.audio_out},
        {speaker.right_in,   mixer.audio_out},

    };

    fprintf(stderr, "Press q to quit\n");

    while(!keys.quit);

    SDL_Quit();

    return 0;
}