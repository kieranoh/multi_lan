#include <iostream>
#include <regex>
#include <tuple>
#include <string>

/* Ellenőrizze, hogy a megadott e-mail cím érvényes-e. Például, abc.123@def.ghi.com.uk egy érvényes e-mail cím. Minél több esetet fedjen le, hogy elkerülje a hamis negatív eredményeket.

@param email Az ellenőrizendő e-mail cím
@return Egy tuple, amelynek első eleme egy boolean, amely jelzi, hogy az e-mail érvényes-e, a második elem pedig a használt minta az e-mail ellenőrzésére. */
std::tuple<bool, std::string> check_email(const std::string& email) {
    // E-mail validáló minta
    const std::string pattern = R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})(:\d{1,5})?$)";
    std::regex email_regex(pattern);
    bool is_valid = std::regex_match(email, email_regex);
    return std::make_tuple(is_valid, pattern);
}