#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 移除子域前缀前后的空白字符
    std::string trimmed_subdomain = subdomain_prefix;
    
    // 移除前导空白
    trimmed_subdomain.erase(trimmed_subdomain.begin(), 
                           std::find_if(trimmed_subdomain.begin(), trimmed_subdomain.end(),
                                       [](unsigned char ch) { return !std::isspace(ch); }));
    
    // 移除尾部空白
    trimmed_subdomain.erase(std::find_if(trimmed_subdomain.rbegin(), trimmed_subdomain.rend(),
                                        [](unsigned char ch) { return !std::isspace(ch); }).base(),
                           trimmed_subdomain.end());
    
    // 构建URL
    std::string url = "https://";
    
    if (!trimmed_subdomain.empty()) {
        // 添加子域前缀和点
        url += trimmed_subdomain + ".";
    }
    
    // 添加主域
    url += domain;
    
    return url;
}