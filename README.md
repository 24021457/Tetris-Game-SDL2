Nguyễn Lý Việt Hải, MSV: 24021457
*Tetris là trò chơi xếp hình cổ điển, nơi người chơi điều khiển các khối hình rơi xuống và cố gắng xếp chúng thành hàng ngang hoàn chỉnh để ghi điểm và tránh để các khối chồng lên nhau đến đỉnh màn hình.
*Ngưỡng điểm: 8-9
*Các lý do: 
Tính năng đã cài đặt
- Giao diện đồ họa bằng SDL2
- Hiển thị **khối kế tiếp (next Tetromino)**
- Hiển thị **score**, **level** tăng theo số hàng đã xóa
- Phát triển hệ thống **âm thanh** bằng SDL_mixer

Thuật toán và logic đã tự cài đặt
- Hệ thống ma trận lưới (grid) để xử lý va chạm và cố định khối
- Thuật toán kiểm tra hàng đầy và xóa hàng
- Xử lý xoay khối với kiểm tra hợp lệ (chống xoay vào tường hoặc chồng lên khối khác)
- Cập nhật mức độ khó bằng cách tăng level và tăng tốc độ rơi khối

Thuật toán tham khảo
- Tạo khối Tetromino ngẫu nhiên từ 7 loại cơ bản (I, J, L, O, S, T, Z)

 Kỹ năng tự học
- Tự học và sử dụng thư viện **SDL2**, **SDL_ttf** để hiển thị chữ, và **SDL_mixer** để xử lý âm thanh
- Tổ chức code rõ ràng: tách riêng các class `Game`, `Grid`, `Tetromino`, `Sound` và file `constants.h`


---

**Xin cảm ơn thầy/cô đã dành thời gian xem xét bài làm của em.**
