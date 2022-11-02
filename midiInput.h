#pragma once

#include "RtMidi.h"

#include <vector>

enum MidiDefines
{
    NUM_NOTES = 128,
    NUM_PARAMS = 128,
};

struct MidiParameter
{
    unsigned index;
    float minValue;
    float maxValue;
};

static float notes[NUM_NOTES];
static MidiParameter params[NUM_PARAMS];

class MidiInput
{
public:
    MidiInput();
    ~MidiInput();
    void init();

private:
    RtMidiIn* midiin;
    void usage();
    bool chooseMidiPort( RtMidiIn *rtmidi );
};