#include "envelope.hpp"

namespace ModSynth
{
    
void Envelope::update() {
    if (gate_in <= 0.0f) {
        state = RELEASE;
    } else if (state == RELEASE) {
        state = ATTACK;
    }

    switch (state) {
    case ATTACK:
        amplitude_out += dt / attack;
        if (amplitude_out >= 1.0f) {
            amplitude_out = 1.0f;
            state = DECAY;
        }
        break;

    case DECAY:
        amplitude_out *= std::exp2(-dt / decay);
        break;

    case RELEASE:
        amplitude_out *= std::exp2(-dt / release);
        break;
    }
}

};