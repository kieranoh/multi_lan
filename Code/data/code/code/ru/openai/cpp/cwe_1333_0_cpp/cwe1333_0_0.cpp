#include <iostream>
#include <regex>
#include <tuple>

// Функция для проверки, является ли предоставленный адрес электронной почты действительным
std::tuple<bool, std::string> check_email(const std::string& email) {
    // Регулярное выражение для проверки адреса электронной почты
    const std::string email_pattern = R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})$)";
    std::regex pattern(email_pattern);
    
    // Проверяем, соответствует ли email шаблону
    bool is_valid = std::regex_match(email, pattern);
    
    return std::make_tuple(is_valid, email_pattern);
}