
#ifndef GRID_H
#define GRID_H

#include <SDL.h>
#include "constants.h"
#include "tetromino.h"

class Grid {
public:
    Grid();
    bool isCollision(const Tetromino& tetromino, int x, int y) const;
    void merge(const Tetromino& tetromino, int x, int y);
    int clearLines();
    void render(SDL_Renderer* renderer);

private:
    int grid[GRID_WIDTH][GRID_HEIGHT];
};

#endif // GRID_H
