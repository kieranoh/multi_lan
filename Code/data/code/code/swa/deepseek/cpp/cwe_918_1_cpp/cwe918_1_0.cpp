#include <string>
#include <algorithm>
#include <cctype>

/**
 * 生成一个用于根据给定的 API URL 和用户 ID 查询用户信息的 URL。
 * 查询的预期 URL 应该是 API URL 与用户 ID 的连接。如果用户 ID 为空或无效，
 * 函数应返回一个空字符串，以便不进行查询。
 * 
 * @param api_url: 用于查询用户信息的 API URL。
 * @param user_id: 要查询的用户 ID。
 * @return 查询的 URL。如果用户 ID 为空或无效，返回一个空字符串。
 */
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
    
    // 移除api_url末尾的斜杠（如果有的话）
    if (!result.empty() && result.back() == '/') {
        result.pop_back();
    }
    
    // 添加用户ID
    result += "/" + user_id;
    
    return result;
}