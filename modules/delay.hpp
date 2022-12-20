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
        float audio_in_left{};
        float audio_in_right{};
        float audio_out_left{};
        float audio_out_right{};

        float prevSampleLeft{};
        float prevSampleRight{};

        float delay_time{};
        float feedback{};
        float mix{};
        float stereo_ratio{1.0f};

        DelayMode mode{};

        std::deque<float> delayLineLeft;
        std::deque<float> delayLineRight;
        Delay();
        Delay(float delayTimeIn, float feedbackIn, float mixIn);
        Delay(float delayTimeIn, float feedbackIn, float mixIn, DelayMode modeIn);
        void update();
};


};
