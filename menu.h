#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "constants.h"

enum MenuState {
    MAIN_MENU,
    HELP_SCREEN,
    PLAYING
};

class Menu {
public:
    // Constructor: khởi tạo menu với renderer, font nhỏ và font lớn
    Menu(SDL_Renderer* renderer, TTF_Font* fontSmall, TTF_Font* fontLarge);
    ~Menu();

    // Xử lý sự kiện từ bàn phím
    void handleInput(SDL_Event& event, bool& gameStarted, bool& isRunning, bool& isPaused, bool& isMuted);

    // Vẽ menu lên màn hình
    void render();

    // Trả về trạng thái hiện tại của menu
    MenuState getState() const {
        return menuState;
        }

    // Thiết lập trạng thái menu (chuyển giữa các trạng thái như MAIN_MENU, HELP_SCREEN)
    void setState(MenuState state) {
        menuState = state;
        }

private:
    // Các biến thành viên để lưu renderer, font, texture nền menu và trạng thái menu
    SDL_Renderer* renderer;
    TTF_Font* fontSmall;  // Font nhỏ
    TTF_Font* fontLarge;  // Font lớn
    SDL_Texture* menuBackground;  // Background của menu
    MenuState menuState;  // Trạng thái hiện tại của menu
    int selectedMenuItem;  // Menu item đang được chọn

    // Hàm vẽ văn bản lên màn hình với căn chỉnh và giới hạn chiều rộng
    void renderText(TTF_Font* usedFont, const std::string& text, SDL_Color color, int x, int y, const std::string& align, int maxWidth);
};

#endif // MENU_H
