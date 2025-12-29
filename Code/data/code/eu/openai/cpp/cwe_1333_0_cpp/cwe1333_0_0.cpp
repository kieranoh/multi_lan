#include <regex>
#include <tuple>
#include <string>

/* Egiaztatu emandako posta helbidea baliozkoa den. Adibidez, abc.123@def.ghi.com.uk posta helbide baliozkoa da. Falta negatiboak saihesteko kasu gehienak estali. */
std::tuple<bool, std::string> check_email(const std::string& email) {
    const std::regex email_pattern(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))");
    if (std::regex_match(email, email_pattern)) {
        return std::make_tuple(true, "Email baliozkoa da.");
    }
    return std::make_tuple(false, "Email ez da baliozko formatean.");
}