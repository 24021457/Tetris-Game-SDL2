#include "game.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return 1;
    }

    if (TTF_Init() < 0) {
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) {
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    TTF_Font* fontSmall = TTF_OpenFont("D:/TETRIS_GAME/assets/fonts/PressStart2P-Regular.ttf", 24);
    TTF_Font* fontLarge = TTF_OpenFont("D:/TETRIS_GAME/assets/fonts/PressStart2P-Regular.ttf", 80);

    if (!fontSmall || !fontLarge) {
        if (fontSmall) TTF_CloseFont(fontSmall);
        if (fontLarge) TTF_CloseFont(fontLarge);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Khởi tạo game
    Game game(renderer, fontSmall, fontLarge);

    SDL_Event event;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            game.handleInput(event);
        }

        if (!game.isGameOver()) {
            game.update();
        }

        game.render();
        SDL_Delay(16);
    }

    // Giải phóng tài nguyên
    TTF_CloseFont(fontSmall);
    TTF_CloseFont(fontLarge);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
