#include <string>
#include <tuple>
#include <regex>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // メールアドレスの正規表現パターン
    const std::regex email_pattern(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})$)");
    
    // 正規表現を使用してメールアドレスを確認
    bool is_valid = std::regex_match(email, email_pattern);
    
    // パターンを文字列として返す
    std::string pattern_used = is_valid ? "Valid email pattern used." : "Invalid email pattern.";
    
    return std::make_tuple(is_valid, pattern_used);
}