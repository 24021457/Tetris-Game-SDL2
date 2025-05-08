#ifndef TETRIS_CONSTANTS_H
#define TETRIS_CONSTANTS_H

#include <SDL.h>

// Kích thước ô
const int BLOCK_SIZE = 30;

// Kích thước lưới
const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 20;

// Kích thước bảng thông tin
const int INFO_PANEL_WIDTH = 300;

// Kích thước cửa sổ
const int SCREEN_WIDTH = GRID_WIDTH * BLOCK_SIZE + INFO_PANEL_WIDTH + 150;
const int SCREEN_HEIGHT = GRID_HEIGHT * BLOCK_SIZE + 100;

// Kích thước vùng chơi
const int GRID_PIXEL_WIDTH = GRID_WIDTH * BLOCK_SIZE;
const int GRID_PIXEL_HEIGHT = GRID_HEIGHT * BLOCK_SIZE;

// Offset để căn giữa lưới
const int GRID_OFFSET_X = 50;
const int GRID_OFFSET_Y = (SCREEN_HEIGHT - GRID_PIXEL_HEIGHT) / 2;

// Vị trí hiển thị thông tin
const int INFO_TEXT_OFFSET_X = GRID_WIDTH * BLOCK_SIZE + GRID_OFFSET_X + 30;
const int INFO_TEXT_OFFSET_Y = GRID_OFFSET_Y;

// Độ dày viền lưới
const int GRID_BORDER_THICKNESS = 5;

// Màu sắc SDL
const SDL_Color COLOR_BLACK  = {0, 0, 0, 255};             // Màu đen
const SDL_Color COLOR_WHITE  = {255, 255, 255, 255};       // Màu trắng
const SDL_Color COLOR_RED    = {255, 0, 0, 255};           // Màu đỏ
const SDL_Color COLOR_BLUE   = {0, 0, 255, 255};           // Màu xanh dương
const SDL_Color COLOR_CYAN   = {0, 255, 255, 255};         // Màu xanh lam
const SDL_Color COLOR_ORANGE = {255, 165, 0, 255};         // Màu cam
const SDL_Color COLOR_YELLOW = {255, 255, 0, 255};         // Màu vàng
const SDL_Color COLOR_GREEN  = {0, 255, 0, 255};           // Màu xanh lá
const SDL_Color COLOR_PURPLE = {128, 0, 128, 255};         // Màu tím
const SDL_Color COLOR_MAGENTA= {255, 0, 255, 255};         // Màu tím nhạt hơn
const SDL_Color COLOR_GRID_BORDER = COLOR_WHITE ;          // Màu viền lưới
const SDL_Color COLOR_GAME_OVER_BG = {100, 100, 100, 255}; // Màu nền khung kết thúc trò chơi

// Hằng số độ khó
const int BASE_DROP_INTERVAL = 800; // Thời gian rơi cơ bản (ms) ở cấp độ 1
const int DROP_INTERVAL_DECREMENT = 100; // Giảm thời gian rơi mỗi cấp độ (ms)
const int MIN_DROP_INTERVAL = 30; // Thời gian rơi tối thiểu (ms)
const int LINES_PER_LEVEL = 4; // Số hàng cần xóa để tăng cấp độ
const Uint32 HIGH_SCORE_DISPLAY_TIME = 3000; // Thời gian hiển thị điểm cao mới (ms)

#endif // TETRIS_CONSTANTS_H
