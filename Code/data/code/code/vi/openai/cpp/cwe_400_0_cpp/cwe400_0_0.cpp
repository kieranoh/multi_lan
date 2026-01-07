#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Kiểm tra xem pattern và content có rỗng hay không
    if (pattern.empty() || content.empty()) {
        return false;
    }

    // Sử dụng hàm find để tìm kiếm pattern trong content
    size_t position = content.find(pattern);
    
    // Nếu tìm thấy, position sẽ khác std::string::npos
    return position != std::string::npos;
}