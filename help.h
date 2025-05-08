#ifndef HELP_H
#define HELP_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "constants.h"
#include <string>

class Help {
public:
    Help(SDL_Renderer* renderer, TTF_Font* font);
    void render();
private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    void renderText(const std::string& text, SDL_Color color, int x, int y, const std::string& align, int maxWidth);
};

#endif // HELP_H
