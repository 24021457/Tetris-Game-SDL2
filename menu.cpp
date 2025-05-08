#include "menu.h"
#include <SDL_image.h>
#include <iostream>

Menu::Menu(SDL_Renderer* renderer, TTF_Font* fontSmall, TTF_Font* fontLarge)
    : renderer(renderer), fontSmall(fontSmall), fontLarge(fontLarge), menuState(MAIN_MENU), selectedMenuItem(0) {
    SDL_Surface* backgroundSurface = IMG_Load("D:/TETRIS_GAME/assets/background.png");

    menuBackground = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);
}

Menu::~Menu() {
    if (menuBackground) {
        SDL_DestroyTexture(menuBackground);
        menuBackground = nullptr;
    }
}

void Menu::handleInput(SDL_Event& event, bool& gameStarted, bool& isRunning, bool& isPaused, bool& isMuted) {
    if (event.type != SDL_KEYDOWN) return;

    if (menuState == MAIN_MENU) {
        if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN) {
            selectedMenuItem = (selectedMenuItem == 0) ? 1 : 0;
        }
        else if (event.key.keysym.sym == SDLK_RETURN) {
            if (selectedMenuItem == 0) {
                menuState = PLAYING;
                gameStarted = true;
                isRunning = true;
            }
            else {
                menuState = HELP_SCREEN;
            }
        }
    }

    else if (menuState == HELP_SCREEN) {
        if (event.key.keysym.sym == SDLK_RETURN) {
            menuState = MAIN_MENU;
        }
    }
}

void Menu::renderText(TTF_Font* usedFont, const std::string& text, SDL_Color color, int x, int y, const std::string& align, int maxWidth) {
    SDL_Surface* surface = TTF_RenderText_Solid(usedFont, text.c_str(), color);
    if (!surface) return;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        return;
    }

    int width = std::min(surface->w, maxWidth);
    SDL_Rect dstRect;
    dstRect.w = width;
    dstRect.h = surface->h;

    if (align == "center") {
        dstRect.x = x - width / 2;
    }
    else {
        dstRect.x = x;
    }
    dstRect.y = y;


    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Menu::render() {
    if (menuState == MAIN_MENU) {
        if (menuBackground) {
            SDL_Rect dstRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
            SDL_RenderCopy(renderer, menuBackground, nullptr, &dstRect);
        }

        SDL_Color colors[] = {
            COLOR_BLUE,     // T - Blue
            COLOR_RED,      // E - Red
            COLOR_GREEN,    // T - Green
            COLOR_MAGENTA,  // R - Magenta
            COLOR_YELLOW,   // I - Yellow
            COLOR_CYAN      // S - Cyan
        };
        std::string tetris = "TETRIS";
        int totalWidth = 0;
        int letterWidths[6];

        for (int i = 0; i < tetris.length(); ++i) {
            std::string letter(1, tetris[i]);
            SDL_Surface* surface = TTF_RenderText_Solid(fontLarge, letter.c_str(), colors[i]);
            if (surface) {
                letterWidths[i] = std::min(surface->w, SCREEN_WIDTH - 20);
                totalWidth += letterWidths[i];
                SDL_FreeSurface(surface);
            }
        }

        int startX = (SCREEN_WIDTH - totalWidth) / 2;
        int currentX = startX;

        for (int i = 0; i < tetris.length(); ++i) {
            std::string letter(1, tetris[i]);
            renderText(fontLarge, letter, colors[i], currentX, SCREEN_HEIGHT / 4, "left", SCREEN_WIDTH - 20);
            currentX += letterWidths[i];
        }

        SDL_Color playColor = (selectedMenuItem == 0) ? COLOR_RED : COLOR_WHITE;
        SDL_Color helpColor = (selectedMenuItem == 1) ? COLOR_RED : COLOR_WHITE;

        renderText(fontSmall, "PLAY", playColor, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, "center", SCREEN_WIDTH - 20);
        renderText(fontSmall, "HELP", helpColor, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 40, "center", SCREEN_WIDTH - 20);
        renderText(fontSmall, "Use UP/DOWN to select, ENTER to confirm", COLOR_BLUE, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100, "center", SCREEN_WIDTH - 20);
    }
}
