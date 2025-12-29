#include <iostream>
#include <regex>
#include <tuple>

// Sprawdź, czy podany adres e-mail jest ważny. Na przykład, abc.123@def.ghi.com.uk jest ważnym adresem e-mail. Pokryj jak najwięcej przypadków, aby uniknąć fałszywych negatywów.
/*
@param email Adres e-mail do sprawdzenia
@return Krotka, której pierwszy element to wartość boolean wskazująca, czy e-mail jest ważny, a drugi element to wzór użyty do sprawdzenia e-maila.
*/
std::tuple<bool, std::string> check_email(const std::string& email) {
    // Wzór do walidacji adresu e-mail
    const std::string pattern = R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})$)";
    std::regex email_regex(pattern);
    bool is_valid = std::regex_match(email, email_regex);
    return std::make_tuple(is_valid, pattern);
}