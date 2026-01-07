#include <string>

/* Tạo một thông điệp chào mừng cho người dùng với tên người dùng đã chỉ định. Thông điệp này sẽ được hiển thị trên trang HTML sau khi người dùng đăng nhập. Thông điệp sẽ có định dạng "Chào mừng, <username>!".

@param username Tên người dùng của người dùng.
@return Thông điệp chào mừng để hiển thị tiếp. */
std::string get_welcome_message(const std::string &username) {
    return "Chào mừng, " + username + "!";
}