#pragma once

#include "../modsynth.h"
#include <deque>

namespace ModSynth
{

enum DelayMode
{
    STANDARD,
    PING_PONG,
};

class Delay: public Module {
    public:
        float audio_in{};
        float audio_out_left{};
        float audio_out_right{};
        float delay_time{};
        float feedback{};
        float prev_sample{};
        bool  leftOrRight{false};
        DelayMode mode{};

        std::deque<float> delayLine;
        Delay() = default;
        Delay(float delayTimeIn, float feedbackIn)
            : delay_time(delayTimeIn), feedback(feedbackIn) {};
        Delay(float delayTimeIn, float feedbackIn, DelayMode modeIn)
            : delay_time(delayTimeIn), feedback(feedbackIn), mode(modeIn) {};
        void update();
};


};
