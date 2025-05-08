#include "tetromino_bag.h"
#include <algorithm>

TetrominoBag::TetrominoBag() {
    fillBag();
}

void TetrominoBag::fillBag() {
    tetrominoBag = {
        TetrominoType::I, TetrominoType::O, TetrominoType::T,
        TetrominoType::S, TetrominoType::Z, TetrominoType::J, TetrominoType::L
    };
    std::random_shuffle(tetrominoBag.begin(), tetrominoBag.end());
}

Tetromino TetrominoBag::getNextTetromino() {
    if (tetrominoBag.empty()) {
        fillBag();
    }
    TetrominoType type = tetrominoBag.back();
    tetrominoBag.pop_back();
    return Tetromino(type);
}

