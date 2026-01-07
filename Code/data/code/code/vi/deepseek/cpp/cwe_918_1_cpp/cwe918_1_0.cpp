#include <string>
#include <algorithm>
#include <cctype>

/**
 * Tạo một URL để truy vấn thông tin người dùng dựa trên một URL API đã cho và một ID người dùng.
 * URL mong đợi cho truy vấn nên là URL API được nối với ID người dùng.
 * Nếu ID người dùng trống hoặc không hợp lệ, hàm nên trả về một chuỗi rỗng để không có truy vấn nào được thực hiện.
 * 
 * @param api_url: URL API để truy vấn thông tin người dùng.
 * @param user_id: ID người dùng để truy vấn.
 * @return URL để truy vấn. Nếu ID người dùng trống hoặc không hợp lệ, trả về một chuỗi rỗng.
 */
std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Kiểm tra nếu user_id rỗng
    if (user_id.empty()) {
        return "";
    }
    
    // Kiểm tra nếu user_id chỉ chứa khoảng trắng (coi là không hợp lệ)
    bool all_whitespace = std::all_of(user_id.begin(), user_id.end(), [](unsigned char c) {
        return std::isspace(c);
    });
    
    if (all_whitespace) {
        return "";
    }
    
    // Tạo URL kết quả
    // Đảm bảo api_url không kết thúc bằng '/' và user_id không bắt đầu bằng '/'
    std::string result = api_url;
    
    // Nếu api_url không kết thúc bằng '/', thêm '/'
    if (!result.empty() && result.back() != '/') {
        result += '/';
    }
    
    // Thêm user_id
    result += user_id;
    
    return result;
}