#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 检查子域前缀是否为空或无效（只包含空白字符）
    bool subdomain_valid = false;
    for (char c : subdomain_prefix) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            subdomain_valid = true;
            break;
        }
    }
    
    // 构建URL
    std::string url = "https://";
    
    if (subdomain_valid) {
        // 添加子域前缀
        url += subdomain_prefix;
        // 确保子域前缀后有点号分隔
        if (!subdomain_prefix.empty() && subdomain_prefix.back() != '.') {
            url += '.';
        }
    }
    
    // 添加主域
    url += domain;
    
    return url;
}