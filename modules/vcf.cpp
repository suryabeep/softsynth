#include "vcf.hpp"

namespace ModSynth
{

void VCF::update() {
    if (type == FilterType::TWO_POLE)
    {
        // https://www.musicdsp.org/en/latest/Filters/29-resonant-filter.html
        audio_in = audio_in * 0.5f + 0.5f;  // domain shift into [0, 1]
        // f and fb calculation
        float f = fmax(fmin(cutoff + contour, 0.99f), 0.01f);
        /* you can approximate this with f = 2.0*pi*freq/samplerate with tuning error towards nyquist */
        float fb = resonance + resonance / (1.0 - f);

        // loop
        float hp = audio_in - out2;
        float bp = out2 - out1;
        out1 = out1 + f * (hp + fb * bp);
        out2 = out2 + f * (out1 - out2);

        if (mode == FilterMode::LOWPASS)
        {
            audio_out = out2;
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
    else if (type == FilterType::FOUR_POLE)
    {
        // https://www.musicdsp.org/en/latest/Filters/26-moog-vcf-variation-2.html
        float f = (cutoff + contour);
        f = fmax(fmin(f, 0.99f), 0.01f);    // clamp, f must be in [0, 1)
        float fb = resonance * (1.0 - 0.15 * f * f);
        audio_in -= out4 * fb;
        audio_in *= 0.35013 * (f*f)*(f*f);
        out1 = audio_in + 0.3 * in1 + (1 - f) * out1; // Pole 1
        in1  = audio_in;
        out2 = out1 + 0.3 * in2 + (1 - f) * out2;  // Pole 2
        in2  = out1;
        out3 = out2 + 0.3 * in3 + (1 - f) * out3;  // Pole 3
        in3  = out2;
        out4 = out3 + 0.3 * in4 + (1 - f) * out4;  // Pole 4
        in4  = out3;
        if (mode == FilterMode::LOWPASS)
        {
            audio_out = out4;
        }
        else if (mode == FilterMode::HIGHPASS)
        {
            audio_out = audio_in - out4;
        }
        else if (mode == FilterMode::BANDPASS)
        {
            audio_out = out4 - out1;
        }
    }
}

};