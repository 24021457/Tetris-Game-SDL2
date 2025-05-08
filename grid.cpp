#include "grid.h"

Grid::Grid() : grid{0} {}

bool Grid::isCollision(const Tetromino& tetromino, int x, int y) const {
    for (int ty = 0; ty < tetromino.getSize(); ty++) {
        for (int tx = 0; tx < tetromino.getSize(); tx++) {
            if (tetromino.getCell(tx, ty)) {
                int gridX = x + tx;
                int gridY = y + ty;
                if (gridX < 0 || gridX >= GRID_WIDTH || gridY >= GRID_HEIGHT || (gridY >= 0 && grid[gridX][gridY] != 0)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Grid::merge(const Tetromino& tetromino, int x, int y) {
    for (int ty = 0; ty < tetromino.getSize(); ty++) {
        for (int tx = 0; tx < tetromino.getSize(); tx++) {
            if (tetromino.getCell(tx, ty)) {
                int gridX = x + tx;
                int gridY = y + ty;
                if (gridY >= 0 && gridY < GRID_HEIGHT && gridX >= 0 && gridX < GRID_WIDTH) {
                    grid[gridX][gridY] = tetromino.getCell(tx, ty);
                }
            }
        }
    }
}

int Grid::clearLines() {
    int linesCleared = 0;
    for (int y = GRID_HEIGHT - 1; y >= 0; y--) {
        bool fullLine = true;
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid[x][y] == 0) {
                fullLine = false;
                break;
            }
        }

        if (fullLine) {
            linesCleared++;
            for (int yy = y; yy > 0; yy--) {
                for (int x = 0; x < GRID_WIDTH; x++) {
                    grid[x][yy] = grid[x][yy - 1];
                }
            }
            for (int x = 0; x < GRID_WIDTH; x++) {
                grid[x][0] = 0;
            }
            y++;
        }
    }
    return linesCleared;
}

void Grid::render(SDL_Renderer* renderer) {
    SDL_Color colors[] = {COLOR_CYAN, COLOR_BLUE, COLOR_ORANGE, COLOR_YELLOW, COLOR_GREEN, COLOR_PURPLE, COLOR_RED};
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid[x][y] != 0) {
                SDL_SetRenderDrawColor(renderer, colors[grid[x][y] - 1].r, colors[grid[x][y] - 1].g, colors[grid[x][y] - 1].b, 255);
                SDL_Rect rect = {GRID_OFFSET_X + x * BLOCK_SIZE, GRID_OFFSET_Y + y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, COLOR_WHITE.r, COLOR_WHITE.g, COLOR_WHITE.b, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }
}
