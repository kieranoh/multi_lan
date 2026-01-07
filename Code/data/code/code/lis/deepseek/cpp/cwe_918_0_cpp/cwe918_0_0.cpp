#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 检查域名是否为空
    if (domain.empty()) {
        return "";
    }
    
    // 清理域名：移除前后空白和可能的协议前缀
    std::string cleaned_domain = domain;
    
    // 移除前后空白
    auto not_space = [](char c) { return !std::isspace(static_cast<unsigned char>(c)); };
    auto start = std::find_if(cleaned_domain.begin(), cleaned_domain.end(), not_space);
    auto end = std::find_if(cleaned_domain.rbegin(), cleaned_domain.rend(), not_space).base();
    
    if (start < end) {
        cleaned_domain = std::string(start, end);
    } else {
        cleaned_domain.clear();
    }
    
    if (cleaned_domain.empty()) {
        return "";
    }
    
    // 移除可能的协议前缀
    const std::string https_prefix = "https://";
    const std::string http_prefix = "http://";
    
    if (cleaned_domain.compare(0, https_prefix.length(), https_prefix) == 0) {
        cleaned_domain.erase(0, https_prefix.length());
    } else if (cleaned_domain.compare(0, http_prefix.length(), http_prefix) == 0) {
        cleaned_domain.erase(0, http_prefix.length());
    }
    
    // 移除末尾的斜杠
    while (!cleaned_domain.empty() && cleaned_domain.back() == '/') {
        cleaned_domain.pop_back();
    }
    
    // 清理子域前缀
    std::string cleaned_subdomain = subdomain_prefix;
    
    // 移除前后空白
    start = std::find_if(cleaned_subdomain.begin(), cleaned_subdomain.end(), not_space);
    end = std::find_if(cleaned_subdomain.rbegin(), cleaned_subdomain.rend(), not_space).base();
    
    if (start < end) {
        cleaned_subdomain = std::string(start, end);
    } else {
        cleaned_subdomain.clear();
    }
    
    // 构建最终URL
    std::ostringstream url_stream;
    url_stream << "https://";
    
    if (!cleaned_subdomain.empty()) {
        // 移除子域末尾的点（如果有）
        while (!cleaned_subdomain.empty() && cleaned_subdomain.back() == '.') {
            cleaned_subdomain.pop_back();
        }
        
        // 移除子域开头的点（如果有）
        while (!cleaned_subdomain.empty() && cleaned_subdomain.front() == '.') {
            cleaned_subdomain.erase(0, 1);
        }
        
        // 如果清理后子域不为空，则添加到URL中
        if (!cleaned_subdomain.empty()) {
            url_stream << cleaned_subdomain << ".";
        }
    }
    
    url_stream << cleaned_domain;
    
    return url_stream.str();
}