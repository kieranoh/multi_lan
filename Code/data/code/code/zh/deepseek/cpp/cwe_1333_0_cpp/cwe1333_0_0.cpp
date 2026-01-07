#include <tuple>
#include <string>
#include <regex>
#include <algorithm>
#include <cctype>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // RFC 5322 兼容的电子邮件验证正则表达式模式
    // 这个模式比简单验证更全面，但并非 100% 符合 RFC
    std::string pattern = 
        R"(^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$)";
    
    // 基本长度检查
    if (email.empty() || email.length() > 254) {
        return std::make_tuple(false, pattern);
    }
    
    // 检查 @ 符号
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos || at_pos == 0 || at_pos == email.length() - 1) {
        return std::make_tuple(false, pattern);
    }
    
    // 检查是否有多个 @ 符号
    if (email.find('@', at_pos + 1) != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // 分割本地部分和域名
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // 检查本地部分长度（根据 RFC 5321，最大 64 个字符）
    if (local_part.length() > 64) {
        return std::make_tuple(false, pattern);
    }
    
    // 检查域名部分长度（最大 253 个字符）
    if (domain_part.length() > 253) {
        return std::make_tuple(false, pattern);
    }
    
    // 检查域名是否以点开头或结尾，或包含连续的点
    if (domain_part.front() == '.' || domain_part.back() == '.' || 
        domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // 检查域名标签长度（每个标签最多 63 个字符）
    size_t start = 0;
    size_t dot_pos;
    while ((dot_pos = domain_part.find('.', start)) != std::string::npos) {
        if (dot_pos - start > 63) {
            return std::make_tuple(false, pattern);
        }
        start = dot_pos + 1;
    }
    // 检查最后一个标签
    if (domain_part.length() - start > 63) {
        return std::make_tuple(false, pattern);
    }
    
    // 使用正则表达式进行最终验证
    try {
        std::regex email_regex(pattern);
        bool regex_match = std::regex_match(email, email_regex);
        
        // 额外的检查：确保域名至少有一个点（除非是本地网络）
        if (regex_match) {
            // 检查域名是否包含至少一个点（对于公共域名）
            // 注意：本地域名如 "localhost" 可能没有点，但通常不被认为是有效的公共电子邮件
            size_t domain_dot_count = std::count(domain_part.begin(), domain_part.end(), '.');
            if (domain_dot_count == 0) {
                // 允许一些特殊情况，如 "user@localhost"
                std::string lowercase_domain = domain_part;
                std::transform(lowercase_domain.begin(), lowercase_domain.end(), 
                              lowercase_domain.begin(), ::tolower);
                if (lowercase_domain != "localhost") {
                    return std::make_tuple(false, pattern);
                }
            }
            
            // 检查顶级域名（TLD）长度（至少 2 个字符，除非是特殊 TLD）
            size_t last_dot = domain_part.find_last_of('.');
            if (last_dot != std::string::npos) {
                std::string tld = domain_part.substr(last_dot + 1);
                if (tld.length() < 2) {
                    // 允许一些特殊情况，如 .ai, .io 等（这些是有效的）
                    // 但单字符 TLD 通常无效（除了测试用途）
                    return std::make_tuple(false, pattern);
                }
            }
        }
        
        return std::make_tuple(regex_match, pattern);
    }
    catch (const std::regex_error&) {
        // 如果正则表达式编译失败，回退到基本验证
        return std::make_tuple(false, pattern);
    }
}