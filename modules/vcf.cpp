#include "vcf.hpp"

namespace ModSynth
{

// https://www.musicdsp.org/en/latest/Filters/29-resonant-filter.html
void VCF::update() {
    // f and fb calculation
    float f = fmax(fmin(cutoff + contour, 0.99f), 0.01f);
    /* you can approximate this with f = 2.0*pi*freq/samplerate with tuning error towards nyquist */
    float fb = resonance + resonance / (1.0 - f);

    // loop
    audio_in = audio_in * 0.5f + 0.5f;  // domain shift into [0, 1]
    float hp = audio_in - buf0;
    float bp = buf0 - buf1;
    buf0 = buf0 + f * (hp + fb * bp);
    buf1 = buf1 + f * (buf0 - buf1);

    if (mode == FilterMode::LOWPASS)
    {
        audio_out = buf1;
    }
    if (mode == FilterMode::BANDPASS)
    {
        audio_out = bp;
    }
    if (mode == FilterMode::HIGHPASS)
    {
        audio_out = hp;
    }

    audio_out = 2.0f * audio_out - 1.0f;    // domain shift back into [-1, 1]
}

};