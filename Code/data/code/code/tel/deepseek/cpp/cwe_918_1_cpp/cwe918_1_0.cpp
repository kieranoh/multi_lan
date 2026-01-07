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
    
    // 移除API URL末尾可能存在的斜杠
    std::string cleaned_api_url = api_url;
    while (!cleaned_api_url.empty() && cleaned_api_url.back() == '/') {
        cleaned_api_url.pop_back();
    }
    
    // 构建完整的查询URL
    return cleaned_api_url + "/" + user_id;
}