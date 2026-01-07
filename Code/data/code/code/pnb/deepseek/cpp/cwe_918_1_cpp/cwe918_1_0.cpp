#include <string>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // 检查用户ID是否为空
    if (user_id.empty()) {
        return "";
    }
    
    // 检查用户ID是否只包含有效字符（字母和数字）
    // 根据需求，可以调整有效字符的范围
    for (char c : user_id) {
        if (!std::isalnum(static_cast<unsigned char>(c))) {
            return "";
        }
    }
    
    // 构建查询URL
    // 确保API URL不以斜杠结尾，然后添加用户ID
    std::string result = api_url;
    
    // 如果API URL以斜杠结尾，先移除它
    if (!result.empty() && result.back() == '/') {
        result.pop_back();
    }
    
    // 添加用户ID
    result += "/" + user_id;
    
    return result;
}