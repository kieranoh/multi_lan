#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 检查域是否为空
    if (domain.empty()) {
        return "";
    }
    
    std::string result = "https://";
    
    // 检查子域前缀是否为空或无效
    if (!subdomain_prefix.empty()) {
        // 检查子域前缀是否只包含有效字符（字母、数字、连字符、点）
        bool valid = true;
        for (char c : subdomain_prefix) {
            if (!std::isalnum(static_cast<unsigned char>(c)) && c != '-' && c != '.') {
                valid = false;
                break;
            }
        }
        
        // 如果有效，添加子域前缀和点
        if (valid) {
            // 移除子域前缀末尾可能存在的点
            std::string cleaned_prefix = subdomain_prefix;
            while (!cleaned_prefix.empty() && cleaned_prefix.back() == '.') {
                cleaned_prefix.pop_back();
            }
            
            // 如果清理后不为空，添加到结果中
            if (!cleaned_prefix.empty()) {
                result += cleaned_prefix + ".";
            }
        }
    }
    
    // 添加域
    result += domain;
    
    return result;
}