#include <iostream>
// Các thư viện khác...
using namespace std;

// Hằng số định nghĩa ký tự gạch (ASCII 219 - hình khối đặc)
const char BLOCK = char(219); 

/**
 * Tác dụng: Tắt chế độ chờ phím Enter (Line Input) và tắt hiển thị ký tự khi gõ (Echo).
 * Giúp game nhận điều khiển mượt mà (Real-time input).
 */
void enableRawMode() {}

/**
 * Tác dụng: Xóa vị trí hiện tại của khối gạch trên ma trận board.
 * Dùng để làm sạch bóng cũ trước khi khối di chuyển sang vị trí mới.
 */
void boardDelBlock(){}

/**
 * Tác dụng: Ghi khối gạch (tại tọa độ x, y) vào ma trận board.
 * Dùng để vẽ khối gạch đang rơi hoặc "đóng băng" khối gạch khi chạm đáy.
 */
void block2Board(){}

/**
 * Tác dụng: Xóa màn hình và vẽ lại toàn bộ trạng thái game (Board, Điểm số, Next Block).
 */
void draw(){}

/**
 * Tác dụng: Kiểm tra xem nếu dịch chuyển thêm (dx, dy) thì có va chạm biên hoặc gạch cũ không.
 * Trả về: true nếu đi được, false nếu bị chặn.
 */
bool canMove() {}

/**
 * Tác dụng: Mô phỏng thử góc xoay tiếp theo xem có bị kẹt vào tường hay đè lên gạch khác không.
 */
bool canRotate() {}

/**
 * Tác dụng: Tính toán góc mới và cập nhật biến rotation nếu canRotate() trả về true.
 */
void rotateBlock() {}

/**
 * Tác dụng: Quét hàng trên cùng (dòng 0), nếu có gạch (BLOCK) xuất hiện -> Game Over.
 */
bool isGameOver() {}

/**
 * Tác dụng: Khởi tạo game, vòng lặp chính xử lý Input, Logic rơi tự động và điều phối các hàm con.
 */
void gotoxy(int x, int y) {

    COORD c = { (SHORT)x, (SHORT)y };

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

}

int main(){
    return 0;
}