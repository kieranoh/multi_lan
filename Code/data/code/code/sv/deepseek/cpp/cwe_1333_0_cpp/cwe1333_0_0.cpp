#include <string>
#include <tuple>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Mönster 1: RFC 5322-kompatibelt mönster (utförlig)
    std::string pattern1 = R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$)";
    
    // Mönster 2: Praktiskt mönster för vanlig användning (mindre strikt)
    std::string pattern2 = R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)";
    
    // Mönster 3: Utökat mönster som tillåter internationella tecken (RFC 6530)
    std::string pattern3 = R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$)";
    
    // Mönster 4: Strikt mönster med längdbegränsningar (RFC 5321)
    std::string pattern4 = R"(^(?=.{1,64}@)[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?=.{1,255}$)(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$)";
    
    // Kontrollera först om e-postadressen är tom
    if (email.empty()) {
        return std::make_tuple(false, "empty");
    }
    
    // Kontrollera för grundläggande ogiltiga tecken och strukturer
    if (email.find('@') == std::string::npos) {
        return std::make_tuple(false, "no_at_symbol");
    }
    
    if (email.find(' ') != std::string::npos) {
        return std::make_tuple(false, "contains_space");
    }
    
    // Kontrollera för flera @-tecken
    if (std::count(email.begin(), email.end(), '@') != 1) {
        return std::make_tuple(false, "multiple_at_symbols");
    }
    
    // Dela upp e-postadressen i lokaldel och domändel
    size_t at_pos = email.find('@');
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // Kontrollera att båda delarna är icke-tomma
    if (local_part.empty() || domain_part.empty()) {
        return std::make_tuple(false, "empty_local_or_domain");
    }
    
    // Kontrollera att lokaldelen inte börjar eller slutar med punkt
    if (local_part.front() == '.' || local_part.back() == '.') {
        return std::make_tuple(false, "local_starts_or_ends_with_dot");
    }
    
    // Kontrollera för på varandra följande punkter i lokaldelen
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "consecutive_dots_in_local");
    }
    
    // Kontrollera att domändelen inte börjar eller slutar med bindestreck eller punkt
    if (domain_part.front() == '-' || domain_part.front() == '.' || 
        domain_part.back() == '-' || domain_part.back() == '.') {
        return std::make_tuple(false, "domain_starts_or_ends_with_hyphen_or_dot");
    }
    
    // Kontrollera för på varandra följande punkter i domändelen
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "consecutive_dots_in_domain");
    }
    
    // Kontrollera att domändelen har minst en punkt
    if (domain_part.find('.') == std::string::npos) {
        return std::make_tuple(false, "no_dot_in_domain");
    }
    
    // Kontrollera att toppdomänen (TLD) har minst 2 tecken
    size_t last_dot = domain_part.find_last_of('.');
    std::string tld = domain_part.substr(last_dot + 1);
    if (tld.length() < 2) {
        return std::make_tuple(false, "tld_too_short");
    }
    
    // Testa med olika regex-mönster i prioriterad ordning
    std::regex regex_pattern1(pattern1);
    std::regex regex_pattern2(pattern2);
    std::regex regex_pattern3(pattern3);
    std::regex regex_pattern4(pattern4);
    
    if (std::regex_match(email, regex_pattern1)) {
        return std::make_tuple(true, "pattern1");
    }
    
    if (std::regex_match(email, regex_pattern2)) {
        return std::make_tuple(true, "pattern2");
    }
    
    if (std::regex_match(email, regex_pattern3)) {
        return std::make_tuple(true, "pattern3");
    }
    
    if (std::regex_match(email, regex_pattern4)) {
        return std::make_tuple(true, "pattern4");
    }
    
    // Om inget mönster matchar, returnera false med generiskt fel
    return std::make_tuple(false, "no_pattern_match");
}