#pragma once

#include <initializer_list>
#include <string>
#include <vector>
#include <SDL2/SDL.h>

namespace ModSynth {

static const float dt = 1.0f / 48000;

// Base class for all modules

class Module
{
public:
    Module();
    Module(const Module &other) = delete;
    Module(Module &&other) = delete;
    virtual ~Module();
    virtual void update() = 0;
};

class VCA: public Module {
public:
    // Audio input
    float audio_in{};
    
    // Parameters
    float amplitude{};

    // Audio output
    float audio_out{};

    VCA() = default;
    VCA(float amplitude): amplitude(amplitude) {}
    void update();
};

class Speaker: public Module {
public:
    // Audio input
    float left_in{};
    float right_in{};

    void update();
};

class Wire: public Module {
public:
    // Value input
    float &input;

    // Value output
    float &output;

    Wire(float &output, float &input): input(input), output(output) {}
    void update();
};

}