#include "mixer.hpp"

namespace ModSynth
{
Mixer::Mixer(std::initializer_list<float> weightsIn)
{
    audio_ins.resize(weightsIn.size());
    weights = std::move(weightsIn);
}
void Mixer::update()
{
    float accum = 0;
    for (int i = 0; i < weights.size() && i < audio_ins.size(); i++)
    {
        accum += weights[i] * audio_ins[i];
    }
    audio_out = accum;
}

};