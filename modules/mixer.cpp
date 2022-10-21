#include "mixer.hpp"

namespace ModSynth
{

void Mixer::update()
{
    float total_weights = 0;
    for (int i = 0; i < weights.size() && i < audio_ins.size(); i++)
    {
        total_weights += weights[i];
    }
    float accum = 0;
    for (int i = 0; i < weights.size() && i < audio_ins.size(); i++)
    {
        accum += weights[i] * audio_ins[i] / total_weights;
    }
    audio_out = accum;
}

};