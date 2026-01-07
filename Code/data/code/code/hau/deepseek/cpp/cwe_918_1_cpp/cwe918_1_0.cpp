std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // 检查用户ID是否为空或无效
    if (user_id.empty()) {
        return "";
    }
    
    // 构建查询URL：API URL + '/' + 用户ID
    return api_url + '/' + user_id;
}