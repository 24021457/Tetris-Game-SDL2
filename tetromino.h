#ifndef TETROMINO_H
#define TETROMINO_H

#include <vector>
#include <SDL.h>
#include "constants.h"

// Định nghĩa các loại Tetromino
enum class TetrominoType {
    I, J, L, O, S, T, Z
};

class Tetromino {
public:
    Tetromino(TetrominoType type = TetrominoType::I);

    void render(SDL_Renderer* renderer, int offsetX, int offsetY, bool applyGridOffset = true);
    void rotate();
    int getType() const;
    int getSize() const;
    int getCell(int x, int y) const;

private:
    int type; // Lưu giá trị kiểu Tetromino (chuyển từ TetrominoType sang int)
    int rotation;
    std::vector<std::vector<std::vector<int>>> shapes;
};

#endif // TETROMINO_H
