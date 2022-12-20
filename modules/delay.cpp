#include "delay.hpp"

namespace ModSynth
{

Delay::Delay()
{
    delayLineLeft.push_back(0);
    delayLineRight.push_back(0);
}


Delay::Delay(float delayTimeIn, float feedbackIn, float mixIn)
    : delay_time(delayTimeIn), feedback(feedbackIn), mix(mixIn) 
{
    delayLineLeft.push_back(0);
    delayLineRight.push_back(0);
};

Delay::Delay(float delayTimeIn, float feedbackIn, float mixIn, DelayMode modeIn)
    : delay_time(delayTimeIn), feedback(feedbackIn), mix(mixIn), mode(modeIn) 
{
    delayLineLeft.push_back(0);
    delayLineRight.push_back(0);
};

void Delay::update()
{
    // read - the front() of each line is going to be 0 until enough samples come in to fill up the lines.
    float leftRead = delayLineLeft.front();
    float rightRead = delayLineRight.front();

    // create input for the delay lines
    float outLeft = audio_in_left * (1.0f - feedback) + leftRead * feedback;
    float outRight = audio_in_right * (1.0f - feedback) + rightRead * feedback;

    // write to the delay lines
    if (mode == DelayMode::STANDARD)
    {
        delayLineLeft.push_back(outLeft);
        delayLineRight.push_back(outRight);
    }
    else if (mode == DelayMode::PING_PONG)
    {
        delayLineLeft.push_back(outRight);
        delayLineRight.push_back(outLeft);
    }

    if (delayLineLeft.size() >= delay_time / dt)
    {
        delayLineLeft.pop_front();
    }
    if (delayLineRight.size() >= (mode == DelayMode::PING_PONG ? stereo_ratio : 1.0f) * delay_time / dt)
    {
        delayLineRight.pop_front();
    }

    // form output
    audio_out_left = (1.0f - mix) * audio_in_left + mix * outLeft;
    audio_out_right = (1.0f - mix) * audio_in_right + mix * outRight;
}

};