#include "game.h"
#include <SDL_image.h>
#include <fstream>
#include <iostream>
#include <algorithm>

// Khởi tạo trò chơi

Game::Game(SDL_Renderer* renderer, TTF_Font* fontSmall, TTF_Font* fontLarge)
    : renderer(renderer), fontSmall(fontSmall), fontLarge(fontLarge), isRunning(true), isPaused(false),
      isMuted(false), currentTetromino(TetrominoType::I), grid(), score(0), highScore(0), level(1),
      tetrominoX(0), tetrominoY(0), lastDropTime(SDL_GetTicks()), nextTetromino(TetrominoType::I),
      gameStarted(false), showNewHighScore(false), showGameOver(false), linesCleared(0),
      menu(renderer, fontSmall, fontLarge), tetrominoBag(), helpScreen(renderer, fontSmall), sound() {

    // Kiểm tra khởi tạo SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        isRunning = false;
        return;
    }

    loadHighScore();
    nextTetromino = tetrominoBag.getNextTetromino();
    spawnTetromino();
    if (!isMuted) {
        sound.playIntroMusic(isMuted);
    }
}

Game::~Game() {
    IMG_Quit();
    SDL_Quit();
}


void Game::loadHighScore() {
    std::ifstream inFile("highscore.txt");
    if (inFile.is_open()) {
        inFile >> highScore;
        inFile.close();
    } else {
        highScore = 0;
    }
}


// Lưu điểm cao vào tệp
void Game::saveHighScore() {
    std::ofstream outFile("highscore.txt");
    if (outFile.is_open()) {
        outFile << highScore;
        outFile.close();
    }
}

// Tạo gạch mới
void Game::spawnTetromino() {
    currentTetromino = nextTetromino;
    nextTetromino = tetrominoBag.getNextTetromino();
    tetrominoX = GRID_WIDTH / 2 - currentTetromino.getSize() / 2;
    tetrominoY = 0;
    lastDropTime = SDL_GetTicks(); // Đặt lại thời gian để gạch mới rơi ngay
}


// Khởi động lại trò chơi
void Game::restart() {
    isRunning = true;
    isPaused = false;
    score = 0;
    level = 1;
    linesCleared = 0;
    tetrominoX = GRID_WIDTH / 2 - currentTetromino.getSize() / 2;
    tetrominoY = 0;
    lastDropTime = SDL_GetTicks();

    grid = Grid();
    showNewHighScore = false;
    showGameOver = false;
    gameStarted = true;

    nextTetromino = tetrominoBag.getNextTetromino();
    spawnTetromino();

    if (!isMuted && gameStarted) {
        sound.resumeBackgroundMusic(isMuted);
    }
}

void Game::handleInput(SDL_Event& event) {
    // Xử lý input khi ở menu
    if (menu.getState() == MAIN_MENU || menu.getState() == HELP_SCREEN) {
        menu.handleInput(event, gameStarted, isRunning, isPaused, isMuted);

        // Bắt đầu game từ menu
        if (menu.getState() == PLAYING) {
            gameStarted = true;
            sound.playStartSound(isMuted);
            if (!isMuted) {
                sound.playBackgroundMusic(isMuted);
            }
            restart();
        }

        // Xử lý bật/tắt âm thanh trong menu khi nhấn phím M
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m) {
            isMuted = !isMuted; // Đảo trạng thái âm thanh
            if (isMuted) {
                sound.pauseBackgroundMusic(); // Tạm dừng nhạc nền khi tắt tiếng
            } else {
                sound.playIntroMusic(isMuted); // Phát nhạc intro khi bật tiếng
            }
        }
        return;
    }

    // Chỉ xử lý sự kiện keydown trong game
    if (event.type != SDL_KEYDOWN) return;

    // Bỏ qua nếu game chưa bắt đầu
    if (!gameStarted) return;

    // Xử lý tạm dừng game khi nhấn phím P
    if (event.key.keysym.sym == SDLK_p && isRunning) {
        isPaused = !isPaused;
        if (isPaused) {
            sound.pauseBackgroundMusic();
        }
        else if (!isMuted) {
            sound.resumeBackgroundMusic(isMuted);
        }
        return;
    }

    // Xử lý bật/tắt âm thanh trong game khi nhấn phím M
    if (event.key.keysym.sym == SDLK_m) {
        isMuted = !isMuted;
        if (isMuted) {
            sound.pauseBackgroundMusic();
        } else if (!isPaused) {
            sound.resumeBackgroundMusic(isMuted);
        }
        return;
    }

    // Bỏ qua input nếu game đang tạm dừng
    if (isPaused) return;

    // Xử lý các phím điều khiển trong game
    switch (event.key.keysym.sym) {
        case SDLK_LEFT:
            // Di chuyển khối sang trái nếu không va chạm
            if (!grid.isCollision(currentTetromino, tetrominoX - 1, tetrominoY)) {
                tetrominoX--;
                sound.playMoveSound(isMuted);
            }
            break;

        case SDLK_RIGHT:
            // Di chuyển khối sang phải nếu không va chạm
            if (!grid.isCollision(currentTetromino, tetrominoX + 1, tetrominoY)) {
                tetrominoX++;
                sound.playMoveSound(isMuted);
            }
            break;

        case SDLK_DOWN:
            // Di chuyển khối xuống dưới nếu không va chạm
            if (!grid.isCollision(currentTetromino, tetrominoX, tetrominoY + 1)) {
                tetrominoY++;
                sound.playMoveSound(isMuted);
            }
            break;

        case SDLK_UP:
            // Xoay khối
            currentTetromino.rotate();
            if (grid.isCollision(currentTetromino, tetrominoX, tetrominoY)) {
                // Nếu va chạm, xoay lại vị trí ban đầu
                for (int i = 0; i < 3; i++) {
                    currentTetromino.rotate();
                }
            }
            else {
                sound.playRotateSound(isMuted); // Phát âm thanh xoay
            }
            break;

        case SDLK_SPACE:
            while (!grid.isCollision(currentTetromino, tetrominoX, tetrominoY + 1)) {
                tetrominoY++;
            }
            sound.playDropSound(isMuted);
            break;


        case SDLK_ESCAPE:
            if (isRunning) {
                // Kết thúc game khi nhấn ESC
                grid.merge(currentTetromino, tetrominoX, tetrominoY);
                if (score > highScore) {
                    highScore = score;
                    showNewHighScore = true;
                    newHighScoreTime = SDL_GetTicks();
                    sound.playNewHighScoreSound(isMuted);
                    saveHighScore();
                }
                isRunning = false;
            }
            break;

        case SDLK_RETURN:
            // Quay lại menu chính khi game over
            if (!isRunning && showGameOver) {
                menu.setState(MAIN_MENU);
                sound.playIntroMusic(isMuted); // Phát nhạc intro
                restart(); // Khởi động lại game
            }
            break;

        case SDLK_r:
            // Chơi lại khi game over
            if (!isRunning && showGameOver) {
                restart();
                isRunning = true;
                sound.playStartSound(isMuted);
                if (!isMuted) {
                    sound.playBackgroundMusic(isMuted); // Phát nhạc nền
                }
            }
            break;
    }
}

// Cập nhật trạng thái trò chơi
void Game::update() {
    Uint32 currentTime = SDL_GetTicks();
    if (!isRunning && !showGameOver && !showNewHighScore) {
        // Chỉ chuyển sang màn hình Game Over nếu không hiển thị điểm cao
        showGameOver = true;
        sound.playGameOverSound(isMuted);
        sound.pauseBackgroundMusic();
    }

    if (!gameStarted || !isRunning || isPaused || menu.getState() != PLAYING) {
        return;
    }

    int dropInterval = std::max(MIN_DROP_INTERVAL, BASE_DROP_INTERVAL - static_cast<int>((level - 1) * DROP_INTERVAL_DECREMENT));


    //Kiểm tra xem đã đến lúc rơi khối chưa
    if (currentTime - lastDropTime > static_cast<Uint32>(dropInterval)) {
        if (grid.isCollision(currentTetromino, tetrominoX, tetrominoY + 1)) {
            grid.merge(currentTetromino, tetrominoX, tetrominoY);
            sound.playLandSound(isMuted);
            int lines = grid.clearLines();

            score += lines * 100 * level;

            if (lines > 0) {
                linesCleared += lines;
                level = std::min(1 + linesCleared / LINES_PER_LEVEL, 10);
                sound.playScoreSound(isMuted);
            }

            if (isRunning) {
                spawnTetromino();

                if (grid.isCollision(currentTetromino, tetrominoX, tetrominoY)) {
                    if (score > highScore) {
                        highScore = score;
                        showNewHighScore = true;
                        newHighScoreTime = currentTime;
                        sound.playNewHighScoreSound(isMuted);
                        saveHighScore();
                    }
                    isRunning = false;
                }
            }
        }

        else {
            tetrominoY++;
        }
        lastDropTime = currentTime;
    }
}

// Hiển thị văn bản lên màn hình
void Game::renderText(const std::string& text, SDL_Color color, int x, int y, const std::string& align, int maxWidth) {
    SDL_Surface* surface = TTF_RenderText_Solid(fontSmall, text.c_str(), color);
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

// Vẽ toàn bộ trò chơi
void Game::render() {
    SDL_SetRenderDrawColor(renderer, COLOR_BLACK.r, COLOR_BLACK.g, COLOR_BLACK.b, COLOR_BLACK.a);
    SDL_RenderClear(renderer);

    if (menu.getState() == MAIN_MENU) {
        menu.render();
    } else if (menu.getState() == HELP_SCREEN) {
        helpScreen.render();
    } else if (menu.getState() == PLAYING) {
        grid.render(renderer);

        if (isRunning && !showGameOver) {
            currentTetromino.render(renderer, tetrominoX, tetrominoY, true);

            int textX = INFO_TEXT_OFFSET_X + 10;
            int baseY = INFO_TEXT_OFFSET_Y;
            int nextTetrominoX = textX / BLOCK_SIZE;
            int nextTetrominoY = (baseY + 160) / BLOCK_SIZE;
            nextTetromino.render(renderer, nextTetrominoX, nextTetrominoY, false);
        }

        SDL_SetRenderDrawColor(renderer, COLOR_GRID_BORDER.r, COLOR_GRID_BORDER.g, COLOR_GRID_BORDER.b, COLOR_GRID_BORDER.a);
        SDL_Rect borderRect = {
            GRID_OFFSET_X - GRID_BORDER_THICKNESS,
            GRID_OFFSET_Y - GRID_BORDER_THICKNESS,
            GRID_PIXEL_WIDTH + 2 * GRID_BORDER_THICKNESS,
            GRID_PIXEL_HEIGHT + 2 * GRID_BORDER_THICKNESS
        };
        for (int i = 0; i < GRID_BORDER_THICKNESS; ++i) {
            SDL_RenderDrawRect(renderer, &borderRect);
            borderRect.x += 1;
            borderRect.y += 1;
            borderRect.w -= 2;
            borderRect.h -= 2;
        }

        renderText("Sound: " + std::string(isMuted ? "Off" : "On"), COLOR_WHITE, 10, 10);

        int textX = INFO_TEXT_OFFSET_X + 10;
        int baseY = INFO_TEXT_OFFSET_Y;
        renderText("Best: " + std::to_string(highScore), COLOR_WHITE, textX, baseY);
        renderText("Score: " + std::to_string(score), COLOR_WHITE, textX, baseY + 40);
        renderText("Level: " + std::to_string(level), COLOR_WHITE, textX, baseY + 80);
        renderText("Next:", COLOR_WHITE, textX, baseY + 120);

        if (isPaused && gameStarted && !showGameOver) {
            std::string pauseText = "PAUSED";
            std::string resumeText = "Press P to Resume";
            SDL_Surface* surfacePause = TTF_RenderText_Solid(fontSmall, pauseText.c_str(), COLOR_YELLOW);
            SDL_Surface* surfaceResume = TTF_RenderText_Solid(fontSmall, resumeText.c_str(), COLOR_WHITE);
            if (surfacePause && surfaceResume) {
                int frameWidth = std::max(surfacePause->w, surfaceResume->w) + 40;
                int frameHeight = surfacePause->h + surfaceResume->h + 60;
                int frameX = (SCREEN_WIDTH - frameWidth) / 2;
                int frameY = (SCREEN_HEIGHT - frameHeight) / 2;

                SDL_Rect frameRect = {frameX, frameY, frameWidth, frameHeight};
                SDL_SetRenderDrawColor(renderer, COLOR_GAME_OVER_BG.r, COLOR_GAME_OVER_BG.g, COLOR_GAME_OVER_BG.b, COLOR_GAME_OVER_BG.a);
                SDL_RenderFillRect(renderer, &frameRect);
                SDL_SetRenderDrawColor(renderer, COLOR_WHITE.r, COLOR_WHITE.g, COLOR_WHITE.b, COLOR_WHITE.a);
                SDL_RenderDrawRect(renderer, &frameRect);

                SDL_Texture* texPause = SDL_CreateTextureFromSurface(renderer, surfacePause);
                SDL_Texture* texResume = SDL_CreateTextureFromSurface(renderer, surfaceResume);
                if (texPause && texResume) {
                    SDL_Rect dstPause = {frameX + (frameWidth - surfacePause->w) / 2, frameY + 20, surfacePause->w, surfacePause->h};
                    SDL_Rect dstResume = {frameX + (frameWidth - surfaceResume->w) / 2, frameY + surfacePause->h + 40, surfaceResume->w, surfaceResume->h};
                    SDL_RenderCopy(renderer, texPause, nullptr, &dstPause);
                    SDL_RenderCopy(renderer, texResume, nullptr, &dstResume);
                }
                SDL_FreeSurface(surfacePause);
                SDL_FreeSurface(surfaceResume);
                if (texPause) SDL_DestroyTexture(texPause);
                if (texResume) SDL_DestroyTexture(texResume);
            }
        }

        if (showNewHighScore) {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - newHighScoreTime <= HIGH_SCORE_DISPLAY_TIME) {
                std::string highScoreText = "New High Score!";
                SDL_Surface* surfaceHighScore = TTF_RenderText_Solid(fontSmall, highScoreText.c_str(), COLOR_WHITE);
                if (surfaceHighScore) {
                    int frameWidth = surfaceHighScore->w + 40;
                    int frameHeight = surfaceHighScore->h + 40;
                    int frameX = (SCREEN_WIDTH - frameWidth) / 2;
                    int frameY = (SCREEN_HEIGHT - frameHeight) / 2;

                    SDL_Rect frameRect = {frameX, frameY, frameWidth, frameHeight};
                    SDL_SetRenderDrawColor(renderer, COLOR_GAME_OVER_BG.r, COLOR_GAME_OVER_BG.g, COLOR_GAME_OVER_BG.b, COLOR_GAME_OVER_BG.a);
                    SDL_RenderFillRect(renderer, &frameRect);

                    SDL_SetRenderDrawColor(renderer, COLOR_WHITE.r, COLOR_WHITE.g, COLOR_WHITE.b, COLOR_WHITE.a);
                    SDL_RenderDrawRect(renderer, &frameRect);

                    SDL_Texture* textureHighScore = SDL_CreateTextureFromSurface(renderer, surfaceHighScore);
                    if (textureHighScore) {
                        SDL_Rect dstRectHighScore = {frameX + (frameWidth - surfaceHighScore->w) / 2, frameY + 20, surfaceHighScore->w, surfaceHighScore->h};
                        SDL_RenderCopy(renderer, textureHighScore, nullptr, &dstRectHighScore);
                        SDL_DestroyTexture(textureHighScore);
                    }
                    SDL_FreeSurface(surfaceHighScore);
                }
            } else {
                showNewHighScore = false;
                showGameOver = true; // Chuyển sang màn hình Game Over sau khi hiển thị điểm cao
                sound.playGameOverSound(isMuted);
                sound.pauseBackgroundMusic();
            }
        }

        if (showGameOver && !showNewHighScore) { // Chỉ hiển thị Game Over nếu không hiển thị điểm cao
            std::string gameOverText = "GAME OVER";
            std::string replayText = "Press R to Replay";
            std::string returnText = "Press Enter to Return to Menu";
            SDL_Surface* surfaceGO = TTF_RenderText_Solid(fontSmall, gameOverText.c_str(), COLOR_RED);
            SDL_Surface* surfaceReplay = TTF_RenderText_Solid(fontSmall, replayText.c_str(), COLOR_WHITE);
            SDL_Surface* surfaceReturn = TTF_RenderText_Solid(fontSmall, returnText.c_str(), COLOR_WHITE);
            if (surfaceGO && surfaceReplay && surfaceReturn) {
                int frameWidth = std::max({surfaceGO->w, surfaceReplay->w, surfaceReturn->w}) + 40;
                int frameHeight = surfaceGO->h + surfaceReplay->h + surfaceReturn->h + 80;
                int frameX = (SCREEN_WIDTH - frameWidth) / 2;
                int frameY = (SCREEN_HEIGHT - frameHeight) / 2;

                SDL_Rect frameRect = {frameX, frameY, frameWidth, frameHeight};
                SDL_SetRenderDrawColor(renderer, COLOR_GAME_OVER_BG.r, COLOR_GAME_OVER_BG.g, COLOR_GAME_OVER_BG.b, COLOR_GAME_OVER_BG.a);
                SDL_RenderFillRect(renderer, &frameRect);
                SDL_SetRenderDrawColor(renderer, COLOR_WHITE.r, COLOR_WHITE.g, COLOR_WHITE.b, COLOR_WHITE.a);
                SDL_RenderDrawRect(renderer, &frameRect);

                SDL_Texture* texGO = SDL_CreateTextureFromSurface(renderer, surfaceGO);
                SDL_Texture* texReplay = SDL_CreateTextureFromSurface(renderer, surfaceReplay);
                SDL_Texture* texReturn = SDL_CreateTextureFromSurface(renderer, surfaceReturn);
                if (texGO && texReplay && texReturn) {
                    SDL_Rect dstGO = {frameX + (frameWidth - surfaceGO->w) / 2, frameY + 20, surfaceGO->w, surfaceGO->h};
                    SDL_Rect dstReplay = {frameX + (frameWidth - surfaceReplay->w) / 2, frameY + surfaceGO->h + 40, surfaceReplay->w, surfaceReplay->h};
                    SDL_Rect dstReturn = {frameX + (frameWidth - surfaceReturn->w) / 2, frameY + surfaceGO->h + surfaceReplay->h + 60, surfaceReturn->w, surfaceReturn->h};
                    SDL_RenderCopy(renderer, texGO, nullptr, &dstGO);
                    SDL_RenderCopy(renderer, texReplay, nullptr, &dstReplay);
                    SDL_RenderCopy(renderer, texReturn, nullptr, &dstReturn);
                }
                SDL_FreeSurface(surfaceGO);
                SDL_FreeSurface(surfaceReplay);
                SDL_FreeSurface(surfaceReturn);
                if (texGO) SDL_DestroyTexture(texGO);
                if (texReplay) SDL_DestroyTexture(texReplay);
                if (texReturn) SDL_DestroyTexture(texReturn);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

// Kiểm tra trạng thái kết thúc trò chơi
bool Game::isGameOver() const {
    return showGameOver;
}


