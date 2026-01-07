#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 移除子域前缀前后的空白字符
    std::string trimmed_subdomain = subdomain_prefix;
    
    // 前向修剪
    trimmed_subdomain.erase(trimmed_subdomain.begin(), 
                           std::find_if(trimmed_subdomain.begin(), trimmed_subdomain.end(), 
                                       [](unsigned char ch) { return !std::isspace(ch); }));
    
    // 后向修剪
    trimmed_subdomain.erase(std::find_if(trimmed_subdomain.rbegin(), trimmed_subdomain.rend(), 
                                        [](unsigned char ch) { return !std::isspace(ch); }).base(), 
                           trimmed_subdomain.end());
    
    // 构建URL
    std::string url = "https://";
    
    if (!trimmed_subdomain.empty()) {
        // 检查子域是否只包含有效字符（字母、数字、点、连字符）
        bool is_valid = std::all_of(trimmed_subdomain.begin(), trimmed_subdomain.end(), 
                                   [](char c) {
                                       return std::isalnum(static_cast<unsigned char>(c)) || 
                                              c == '.' || c == '-';
                                   });
        
        if (is_valid && trimmed_subdomain.find("..") == std::string::npos) {
            // 添加子域前缀和点
            url += trimmed_subdomain + "." + domain;
        } else {
            // 无效的子域，直接使用域
            url += domain;
        }
    } else {
        // 空子域，直接使用域
        url += domain;
    }
    
    return url;
}