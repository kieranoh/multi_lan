#include <iostream>
#include <regex>
#include <tuple>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Definice regulárního výrazu pro kontrolu platnosti e-mailu
    const std::string email_pattern = R"(([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}))";
    std::regex pattern(email_pattern);
    
    // Kontrola, zda e-mail odpovídá vzoru
    bool is_valid = std::regex_match(email, pattern);
    
    // Vrátí n-tici, kde první prvek je boolean a druhý prvek je vzor
    return std::make_tuple(is_valid, email_pattern);
}