#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Kiểm tra xem ID người dùng có hợp lệ hay không
    if (user_id.empty()) {
        return ""; // Trả về chuỗi rỗng nếu ID người dùng không hợp lệ
    }
    
    // Nối URL API với ID người dùng
    return api_url + "/" + user_id;
}