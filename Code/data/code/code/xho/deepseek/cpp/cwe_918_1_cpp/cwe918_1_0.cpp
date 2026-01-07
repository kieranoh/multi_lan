#include <string>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // 检查用户ID是否为空
    if (user_id.empty()) {
        return "";
    }
    
    // 检查用户ID是否有效（至少包含一个非空白字符）
    bool has_valid_char = false;
    for (char c : user_id) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            has_valid_char = true;
            break;
        }
    }
    
    if (!has_valid_char) {
        return "";
    }
    
    // 构建查询URL
    // 确保api_url不以斜杠结尾，然后添加斜杠和用户ID
    std::string result = api_url;
    
    // 移除api_url末尾的斜杠（如果有的话）
    if (!result.empty() && result.back() == '/') {
        result.pop_back();
    }
    
    // 添加斜杠和用户ID
    result += '/';
    result += user_id;
    
    return result;
}