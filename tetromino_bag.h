#ifndef TETROMINO_BAG_H
#define TETROMINO_BAG_H

#include <vector>
#include "tetromino.h"

class TetrominoBag {
public:
    TetrominoBag();
    Tetromino getNextTetromino();
    bool isEmpty() const { return tetrominoBag.empty(); }
private:
    std::vector<TetrominoType> tetrominoBag;
    void fillBag();
};

#endif // TETROMINO_BAG_H
