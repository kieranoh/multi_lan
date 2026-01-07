#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 检查域名是否为空
    if (domain.empty()) {
        return "";
    }
    
    // 清理域名：移除前后的空白字符
    std::string cleaned_domain = domain;
    auto not_space = [](char c) { return !std::isspace(static_cast<unsigned char>(c)); };
    cleaned_domain.erase(cleaned_domain.begin(), std::find_if(cleaned_domain.begin(), cleaned_domain.end(), not_space));
    cleaned_domain.erase(std::find_if(cleaned_domain.rbegin(), cleaned_domain.rend(), not_space).base(), cleaned_domain.end());
    
    // 清理子域前缀：移除前后的空白字符
    std::string cleaned_subdomain = subdomain_prefix;
    cleaned_subdomain.erase(cleaned_subdomain.begin(), std::find_if(cleaned_subdomain.begin(), cleaned_subdomain.end(), not_space));
    cleaned_subdomain.erase(std::find_if(cleaned_subdomain.rbegin(), cleaned_subdomain.rend(), not_space).base(), cleaned_subdomain.end());
    
    // 构建URL
    std::string url = "https://";
    
    if (!cleaned_subdomain.empty()) {
        // 添加子域前缀和点
        url += cleaned_subdomain + ".";
    }
    
    // 添加域名
    url += cleaned_domain;
    
    return url;
}