#include "keyboard.hpp"

#include <map>

namespace ModSynth
{


// Keyboard

void Keyboard::update()
{
    static const std::map<char, int> keyToNoteNumberMap = {
        {SDLK_a, 0}, 
        {SDLK_w, 1}, 
        {SDLK_s, 2},
        {SDLK_e, 3}, 
        {SDLK_d, 4}, 
        {SDLK_f, 5}, 
        {SDLK_t, 6}, 
        {SDLK_g, 7}, 
        {SDLK_y, 8}, 
        {SDLK_h, 9}, 
        {SDLK_u, 10}, 
        {SDLK_j, 11}, 
        {SDLK_k, 12}, 
        {SDLK_o, 13}, 
        {SDLK_l, 14}, 
    };

    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
    {
        quit = true;
    }
    else if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_q)
        {
            quit = true;
        }
        else if (event.key.keysym.sym == SDLK_UP)
        {
            octave += 1;
        }
        else if (event.key.keysym.sym == SDLK_DOWN)
        {
            octave -= 1;
        }
        else if (keyToNoteNumberMap.find(event.key.keysym.sym) != keyToNoteNumberMap.end())
        {
            gate_out = 1.0f;
            int noteNumber = keyToNoteNumberMap.at(event.key.keysym.sym);
            frequency_out = 440.0f * std::exp2((noteNumber - 9) / 12.0f + octave - 4);
        }
    }
    else if (event.type == SDL_KEYUP)
    {
        gate_out = -1.0f;
    }
}

};