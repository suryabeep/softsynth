#pragma once

#include "../modsynth.h"

namespace ModSynth
{


class Envelope: public Module {
public:
    // Trigger input
    float gate_in{}; // > 0 triggers attack

    // Parameters
    float attack{}; // seconds
    float decay{};  // seconds/halving
    float release{}; // seconds/halving

    // Output
    float amplitude_out{}; // 0..1

    Envelope() = default;
    Envelope(float attack, float decay, float release): attack(attack), decay(decay), release(release) {}
    void update();

private:
    // Internal state
    enum {
        ATTACK,
        DECAY,
        RELEASE,
    } state;
};


};
