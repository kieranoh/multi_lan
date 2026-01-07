#include <string>
#include <algorithm>
#include <regex>

bool searchPattern(const std::string& pattern, const std::string& content) {
    try {
        // Kiểm tra đầu vào rỗng
        if (pattern.empty() || content.empty()) {
            return false;
        }
        
        // Sử dụng std::search để tìm kiếm mẫu trong nội dung
        auto it = std::search(
            content.begin(), content.end(),
            pattern.begin(), pattern.end()
        );
        
        // Trả về true nếu tìm thấy, false nếu không
        return it != content.end();
    }
    catch (...) {
        // Bắt tất cả các ngoại lệ và trả về false
        return false;
    }
}