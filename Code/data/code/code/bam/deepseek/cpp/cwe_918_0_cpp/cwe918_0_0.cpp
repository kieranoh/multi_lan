#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 清理域名：移除前导和尾随空白字符
    auto clean_string = [](const std::string& str) -> std::string {
        auto start = std::find_if_not(str.begin(), str.end(), [](unsigned char c) {
            return std::isspace(c);
        });
        auto end = std::find_if_not(str.rbegin(), str.rend(), [](unsigned char c) {
            return std::isspace(c);
        }).base();
        return (start < end) ? std::string(start, end) : std::string();
    };

    std::string cleaned_domain = clean_string(domain);
    std::string cleaned_subdomain = clean_string(subdomain_prefix);

    // 如果域名无效，返回空字符串
    if (cleaned_domain.empty()) {
        return "";
    }

    // 构建URL
    std::ostringstream url_stream;
    url_stream << "https://";

    // 如果子域有效，添加子域部分
    if (!cleaned_subdomain.empty()) {
        // 移除子域末尾可能存在的点
        if (cleaned_subdomain.back() == '.') {
            cleaned_subdomain.pop_back();
        }
        // 如果子域在清理后仍然有效，则添加
        if (!cleaned_subdomain.empty()) {
            url_stream << cleaned_subdomain << ".";
        }
    }

    // 添加主域名
    url_stream << cleaned_domain;

    return url_stream.str();
}