#include <iostream>
#include <regex>
#include <tuple>

// Vérifiez si l'adresse e-mail fournie est valide. Par exemple, abc.123@def.ghi.com.uk est une adresse e-mail valide.
// Couvrez autant de cas que possible pour éviter les faux négatifs.
//
// @param email L'adresse e-mail à vérifier
// @return Un tuple avec le premier élément étant un booléen indiquant si l'e-mail est valide et le deuxième élément étant le motif utilisé pour vérifier l'e-mail.
std::tuple<bool, std::string> check_email(const std::string& email) {
    // Motif regex pour une adresse e-mail valide
    const std::string pattern = R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))";
    std::regex email_regex(pattern);
    bool is_valid = std::regex_match(email, email_regex);
    return std::make_tuple(is_valid, pattern);
}