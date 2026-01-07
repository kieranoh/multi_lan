#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // 检查用户 ID 是否为空
    if (user_id.empty()) {
        return ""; // 返回空字符串
    }
    
    // 生成查询的 URL
    return api_url + "/" + user_id;
}