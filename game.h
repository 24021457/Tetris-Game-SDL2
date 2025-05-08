#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "grid.h"
#include "tetromino.h"
#include "menu.h"
#include "tetromino_bag.h"
#include "help.h"
#include "sound.h"
#include "constants.h"

class Game {
public:
    // Constructor nhận renderer, font nhỏ và font lớn
    Game(SDL_Renderer* renderer, TTF_Font* fontSmall, TTF_Font* fontLarge);
    ~Game();

    // Hàm xử lý các sự kiện nhập liệu
    void handleInput(SDL_Event& event);

    // Cập nhật trạng thái game
    void update();

    // Vẽ game lên màn hình
    void render();

    // Kiểm tra nếu game đã kết thúc
    bool isGameOver() const;

    // Khởi động lại game
    void restart();

private:
    // Các biến thành viên của lớp Game
    SDL_Renderer* renderer;      // Renderer để vẽ lên màn hình
    TTF_Font* fontSmall;         // Font nhỏ dùng cho văn bản
    TTF_Font* fontLarge;         // Font lớn dùng cho tiêu đề hoặc các văn bản quan trọng
    bool isRunning;              // Kiểm tra trạng thái game có đang chạy hay không
    bool isPaused;               // Kiểm tra xem game có đang tạm dừng hay không
    bool isMuted;                // Kiểm tra xem âm thanh có bị tắt không
    Tetromino currentTetromino;  // Khối Tetrimino hiện tại
    Grid grid;                  // Mảng lưới để lưu trữ các khối đã rơi
    int score;                   // Điểm số hiện tại
    int highScore;               // Điểm cao nhất
    int level;                   // Mức độ hiện tại của game
    int tetrominoX;              // Vị trí X của Tetromino hiện tại
    int tetrominoY;              // Vị trí Y của Tetromino hiện tại
    Uint32 lastDropTime;         // Thời gian rơi của khối Tetromino
    Tetromino nextTetromino;     // Khối Tetrimino tiếp theo
    bool gameStarted;            // Kiểm tra xem game có bắt đầu hay chưa
    bool showNewHighScore;       // Hiển thị điểm cao mới
    bool showGameOver;           // Hiển thị màn hình kết thúc game
    Uint32 newHighScoreTime;     // Thời gian hiển thị điểm cao mới
    int linesCleared;            // Số dòng đã xóa trong game
    Menu menu;                   // Menu chính của game
    TetrominoBag tetrominoBag;   // Túi Tetromino để lấy khối mới
    Help helpScreen;             // Màn hình trợ giúp
    Sound sound;                 // Quản lý âm thanh của game

    // Các phương thức phụ trợ
    void loadHighScore();        // Tải điểm cao từ tệp
    void saveHighScore();        // Lưu điểm cao vào tệp
    void spawnTetromino();       // Tạo khối Tetromino mới
    void renderText(const std::string& text, SDL_Color color, int x, int y, const std::string& align = "left", int maxWidth = SCREEN_WIDTH - 20);  // Vẽ văn bản
};

#endif // GAME_H
