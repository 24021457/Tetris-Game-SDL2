#include "help.h"

Help::Help(SDL_Renderer* renderer, TTF_Font* font) : renderer(renderer), font(font) {}

void Help::renderText(const std::string& text, SDL_Color color, int x, int y, const std::string& align, int maxWidth) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
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
    } else {
        dstRect.x = x;
    }
    dstRect.y = y;

    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}


void Help::render() {
    int centerX = SCREEN_WIDTH / 2;
    int baseY = SCREEN_HEIGHT / 4;
    renderText("HELP", COLOR_YELLOW, centerX, baseY, "center", SCREEN_WIDTH - 20);

    auto renderHelpLine = [&](const std::string& key, const std::string& desc, int y) {
        SDL_Surface* keySurface = TTF_RenderText_Solid(font, key.c_str(), COLOR_YELLOW);
        SDL_Surface* descSurface = TTF_RenderText_Solid(font, desc.c_str(), COLOR_WHITE);
        if (!keySurface || !descSurface) {
            if (keySurface) SDL_FreeSurface(keySurface);
            if (descSurface) SDL_FreeSurface(descSurface);
            return;
        }

        int totalWidth = keySurface->w + descSurface->w;
        int startX = centerX - totalWidth / 2;

        SDL_Texture* keyTexture = SDL_CreateTextureFromSurface(renderer, keySurface);
        SDL_Rect keyRect = {startX, y, keySurface->w, keySurface->h};
        SDL_RenderCopy(renderer, keyTexture, nullptr, &keyRect);

        SDL_Texture* descTexture = SDL_CreateTextureFromSurface(renderer, descSurface);
        SDL_Rect descRect = {startX + keySurface->w, y, descSurface->w, descSurface->h};
        SDL_RenderCopy(renderer, descTexture, nullptr, &descRect);

        SDL_FreeSurface(keySurface);
        SDL_FreeSurface(descSurface);
        SDL_DestroyTexture(keyTexture);
        SDL_DestroyTexture(descTexture);
    };

    renderHelpLine("P:", "Pause/Resume game", baseY + 40);
    renderHelpLine("M:", "Mute/Unmute sound", baseY + 80);
    renderHelpLine("Left/Right:", "Move tetromino", baseY + 120);
    renderHelpLine("Up:", "Rotate tetromino", baseY + 160);
    renderHelpLine("Down:", "Move down", baseY + 200);
    renderHelpLine("Space:", "Drop tetromino", baseY + 240);
    renderHelpLine("Esc:", "Exit game", baseY + 280);
    renderHelpLine("R:", "Replay after game over", baseY + 320);
    renderText("Press ENTER to return", COLOR_BLUE, centerX, baseY + 360, "center", SCREEN_WIDTH - 20);
}
