#include "tetromino.h"
#include <random>
#include <ctime>

using namespace std;

// Khởi tạo mt19937 với seed dựa trên thời gian
static mt19937 gen(static_cast<unsigned int>(time(nullptr)));

Tetromino::Tetromino(TetrominoType type) : type(static_cast<int>(type)), rotation(0) {
    shapes = {
        {{0,0,0,0},
         {1,1,1,1},
         {0,0,0,0},
         {0,0,0,0}}, // I

        {{1,0,0},
         {1,1,1},
         {0,0,0}}, // J

        {{0,0,1},
         {1,1,1},
         {0,0,0}}, // L

        {{1,1},
         {1,1}}, // O

        {{0,1,1},
         {1,1,0},
         {0,0,0}}, // S

        {{0,1,0},
         {1,1,1},
         {0,0,0}}, // T

        {{1,1,0},
         {0,1,1},
         {0,0,0}}  // Z
    };
}

void Tetromino::rotate() {
    rotation = (rotation + 1) % 4;
}

int Tetromino::getType() const {
    return type;
}

int Tetromino::getSize() const {
    return shapes[type][0].size();
}

int Tetromino::getCell(int x, int y) const {
    int size = getSize();
    if (x < 0 || x >= size || y < 0 || y >= size) {
        return 0;
    }
    switch(rotation % 4) {
        case 0: return shapes[type][y][x];
        case 1: return shapes[type][size - x - 1][y];
        case 2: return shapes[type][size - y - 1][size - x - 1];
        case 3: return shapes[type][x][size - y - 1];
    }
    return 0;
}

void Tetromino::render(SDL_Renderer* renderer, int offsetX, int offsetY, bool applyGridOffset) {
    SDL_Color colors[] = {
        COLOR_CYAN,    // I
        COLOR_BLUE,    // J
        COLOR_ORANGE,  // L
        COLOR_YELLOW,  // O
        COLOR_GREEN,   // S
        COLOR_PURPLE,  // T
        COLOR_RED      // Z
    };

    int size = getSize();
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if (getCell(x, y)) {
                int renderX = (offsetX + x) * BLOCK_SIZE;
                int renderY = (offsetY + y) * BLOCK_SIZE;

                // Chỉ áp dụng GRID_OFFSET_X/Y nếu tetromino nằm trên lưới
                if (applyGridOffset) {
                    renderX += GRID_OFFSET_X;
                    renderY += GRID_OFFSET_Y;
                }

                SDL_Rect rect = {renderX, renderY, BLOCK_SIZE, BLOCK_SIZE};
                SDL_SetRenderDrawColor(renderer, colors[type].r, colors[type].g, colors[type].b, colors[type].a);
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, COLOR_WHITE.r, COLOR_WHITE.g, COLOR_WHITE.b, COLOR_WHITE.a);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }
}
