#include "vcf.hpp"

namespace ModSynth
{

void VCF::update() {
    float f = 2.0f * std::sin(std::min((float)M_PI * cutoff * envelope * dt, std::asin(0.5f)));
    float q = 1.0f / resonance;

    lowpass_out += f * bandpass_out;
    highpass_out = audio_in - q * bandpass_out - lowpass_out;
    bandpass_out += f * highpass_out;
}

};