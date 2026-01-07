#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // 检查用户ID是否为空或无效
    if (user_id.empty()) {
        return "";
    }
    
    // 检查用户ID是否只包含空白字符
    bool is_all_whitespace = std::all_of(user_id.begin(), user_id.end(), [](unsigned char c) {
        return std::isspace(c);
    });
    
    if (is_all_whitespace) {
        return "";
    }
    
    // 构建查询URL
    // 确保api_url不以斜杠结尾，然后添加斜杠和用户ID
    std::string result = api_url;
    
    // 移除api_url末尾的斜杠（如果存在）
    if (!result.empty() && result.back() == '/') {
        result.pop_back();
    }
    
    // 添加用户ID
    result += "/" + user_id;
    
    return result;
}