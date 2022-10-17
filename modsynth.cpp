#include "modsynth.h"

#include <algorithm>
#include <stdexcept>
#include <vector>
#include <mutex>

namespace ModSynth {

// Module registry

static std::vector<Module *> modules;
static std::mutex mutex;

Module::Module() {
    std::lock_guard<std::mutex> lock(mutex);
    modules.push_back(this);
}

Module::~Module() {
    std::lock_guard<std::mutex> lock(mutex);
    modules.erase(std::find(modules.begin(), modules.end(), this));
}

// Audio output

static struct Audio {
    static float left;
    static float right;

    static void callback(void *userdata, uint8_t *stream, int len) {

        std::lock_guard<std::mutex> lock(mutex);
        float *ptr = reinterpret_cast<float *>(stream);

        for (size_t i = 0; i < len / sizeof ptr; i++) {
            left = 0;
            right = 0;

            for (auto mod: modules) {
                mod->update();
            }

            // Make the output a bit softer so we don't immediately clip
            *ptr++ = left * 0.1;
            *ptr++ = right * 0.1;
        }
        
    }

    Audio() {
        if( SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0){
            fprintf( stderr, "Could not initialise SDL: %s\n", SDL_GetError() );
            exit( -1 );
        }

        SDL_Window *window = SDL_CreateWindow(
            "Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
            680, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

        if(!window) {
            fprintf(stderr, "Failed to create window.\n");
            exit(-1);
        }

        // Create renderer and select the color for drawing. 
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        
        SDL_AudioSpec desired{};

        desired.freq = 48000;
        desired.format = AUDIO_F32;
        desired.channels = 2;
        desired.samples = 128;
        desired.callback = callback;

        if (SDL_OpenAudio(&desired, nullptr) != 0) {
            throw std::runtime_error(SDL_GetError());
        }

        SDL_PauseAudio(0);
    }
} audio;

float Audio::left;
float Audio::right;

void VCA::update() {
    audio_out = audio_in * amplitude;
}

void Speaker::update() {
    audio.left += left_in;
    audio.right += right_in;
}

void Wire::update() {
    output = input;
}


}