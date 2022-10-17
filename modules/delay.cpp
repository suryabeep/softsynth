#include "delay.hpp"

namespace ModSynth
{

void Delay::update()
{
    delayLine.push_back(audio_in + feedback * prev_sample);
    float audio_out = audio_in + delayLine.front();
    prev_sample = audio_out;
    if (delayLine.size() >= delay_time / dt)
    {
        delayLine.pop_front();
    }
    if (mode == DelayMode::STANDARD)
    {
        audio_out_left = audio_out;
        audio_out_right = audio_out;
    }
    else if (mode == DelayMode::PING_PONG)
    {   
        audio_out_left  = leftOrRight ? audio_out : audio_in;
        audio_out_right = !leftOrRight ? audio_out : audio_in;
    }
}

};