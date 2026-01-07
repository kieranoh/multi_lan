#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 移除子域前缀的前后空白字符
    auto start = std::find_if_not(subdomain_prefix.begin(), subdomain_prefix.end(), 
                                  [](unsigned char c) { return std::isspace(c); });
    auto end = std::find_if_not(subdomain_prefix.rbegin(), subdomain_prefix.rend(),
                                [](unsigned char c) { return std::isspace(c); }).base();
    std::string trimmed_subdomain(start < end ? std::string(start, end) : "");
    
    // 检查子域前缀是否为空或无效（仅空白字符）
    if (trimmed_subdomain.empty()) {
        return "https://" + domain;
    }
    
    // 移除子域前缀末尾可能存在的点
    while (!trimmed_subdomain.empty() && trimmed_subdomain.back() == '.') {
        trimmed_subdomain.pop_back();
    }
    
    // 如果移除点后子域变为空，则返回域本身
    if (trimmed_subdomain.empty()) {
        return "https://" + domain;
    }
    
    // 构建完整的URL
    return "https://" + trimmed_subdomain + "." + domain;
}