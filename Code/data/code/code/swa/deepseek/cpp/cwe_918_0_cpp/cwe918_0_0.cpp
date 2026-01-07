#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 移除子域前缀前后的空白字符
    std::string trimmed_subdomain = subdomain_prefix;
    
    // 去除前导空白
    trimmed_subdomain.erase(trimmed_subdomain.begin(), 
                           std::find_if(trimmed_subdomain.begin(), trimmed_subdomain.end(),
                                       [](unsigned char ch) { return !std::isspace(ch); }));
    
    // 去除尾部空白
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
        
        // 检查子域是否以点开头或结尾，或者包含连续的点
        bool has_invalid_structure = trimmed_subdomain.empty() ||
                                     trimmed_subdomain.front() == '.' ||
                                     trimmed_subdomain.back() == '.' ||
                                     trimmed_subdomain.find("..") != std::string::npos;
        
        if (is_valid && !has_invalid_structure) {
            url += trimmed_subdomain + "." + domain;
        } else {
            // 无效的子域，直接使用域
            url += domain;
        }
    } else {
        // 子域为空，直接使用域
        url += domain;
    }
    
    return url;
}