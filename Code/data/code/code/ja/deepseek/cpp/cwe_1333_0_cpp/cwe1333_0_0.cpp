#include <tuple>
#include <string>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // RFC 5322に準拠した包括的なメール検証パターン
    std::string pattern = 
        R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*)"
        R"(@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+)"
        R"([a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$)";
    
    std::regex email_regex(pattern);
    
    // 基本的な長さチェック
    if (email.empty() || email.length() > 254) {
        return std::make_tuple(false, pattern);
    }
    
    // ローカルパート（@の前）の長さチェック
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos || at_pos == 0 || at_pos > 64) {
        return std::make_tuple(false, pattern);
    }
    
    // 連続するドットや特殊文字のチェック
    if (email.find("..") != std::string::npos ||
        email.find("@.") != std::string::npos ||
        email.find(".@") != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // ドメイン部分のチェック
    std::string domain = email.substr(at_pos + 1);
    if (domain.empty() || domain.length() > 253) {
        return std::make_tuple(false, pattern);
    }
    
    // トップレベルドメインのチェック（少なくとも2文字）
    size_t last_dot = domain.find_last_of('.');
    if (last_dot == std::string::npos || 
        domain.length() - last_dot - 1 < 2) {
        return std::make_tuple(false, pattern);
    }
    
    // 正規表現による包括的な検証
    bool is_valid = std::regex_match(email, email_regex);
    
    return std::make_tuple(is_valid, pattern);
}