#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // 检查用户 ID 是否为空或无效
    if (user_id.empty()) {
        return "";
    }
    
    // 返回组合后的查询 URL
    return api_url + "/" + user_id;
}