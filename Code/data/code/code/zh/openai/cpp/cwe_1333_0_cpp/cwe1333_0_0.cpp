#include <iostream>
#include <regex>
#include <string>
#include <tuple>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // 定义电子邮件地址的正则表达式模式
    const std::regex email_pattern(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))");
    
    // 检查电子邮件是否符合正则表达式
    bool is_valid = std::regex_match(email, email_pattern);
    
    // 返回结果
    return std::make_tuple(is_valid, is_valid ? "Valid email format" : "Invalid email format");
}