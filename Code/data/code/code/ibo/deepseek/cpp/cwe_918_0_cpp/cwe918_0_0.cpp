#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 检查域名是否为空
    if (domain.empty()) {
        return "";
    }
    
    // 清理域名前后的空白字符
    auto clean_string = [](const std::string& str) -> std::string {
        if (str.empty()) return "";
        
        size_t start = 0;
        size_t end = str.length() - 1;
        
        // 找到第一个非空白字符
        while (start <= end && std::isspace(static_cast<unsigned char>(str[start]))) {
            ++start;
        }
        
        // 找到最后一个非空白字符
        while (end >= start && std::isspace(static_cast<unsigned char>(str[end]))) {
            --end;
        }
        
        if (start > end) return "";
        return str.substr(start, end - start + 1);
    };
    
    std::string cleaned_domain = clean_string(domain);
    std::string cleaned_subdomain = clean_string(subdomain_prefix);
    
    // 构建URL
    std::string url = "https://";
    
    if (!cleaned_subdomain.empty()) {
        // 添加子域前缀
        url += cleaned_subdomain + ".";
    }
    
    // 添加主域名
    url += cleaned_domain;
    
    return url;
}