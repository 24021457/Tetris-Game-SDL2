1. Giới thiệu
   Tetris là trò chơi xếp hình cổ điển, nơi người chơi điều khiển các khối hình rơi xuống và cố gắng xếp chúng thành hàng ngang hoàn chỉnh để ghi điểm và tránh để các khối chồng lên nhau đến đỉnh màn hình.

2. Công nghệ sử dụng
  -Ngôn ngữ C++
  -SDL2
  -SDL2_ttf
  -SDL2_image
  -SDL2_mixer

3. Tính năng
  -Tăng score theo số hàng đã xóa (score = level*100*n) (n là số hàng đã xóa)
  -Tăng level sau khi xóa được 5 hàng
  -Hiển thị khối tiếp theo (Next Tetromino), điểm số hiện tại (Score), điểm cao nhất (Best), cấp độ hiện tại (Level)
  -Khi người chơi đạt được score vượt qua highscore, khi gameover sẽ có thông báo chúc mừng và được lưu vào điểm cao nhất

5. Cách chơi
Trong game có phần Help có hướng dẫn chơi, đây là hướng dẫn cơ bản:
| Phím  | Chức năng              |
| ----- | ---------------------  |
| ←     | Di chuyển sang trái    |
| →     | Di chuyển sang phải    |
| ↓     | Tăng tốc rơi           |
| ↑     | Xoay khối              |
| Space | Rơi nhanh (Hard drop)  |
| Esc   | Thoát trò chơi         |
| P     | Tạm dừng trò chơi      |
| M     | Tắt âm thanh trò chơi  |
