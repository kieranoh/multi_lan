#include <iostream>
#include <string>
#include <tuple>
#include <regex>
#include <algorithm>
#include <cctype>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Tarkista ensin perusasioita ennen regex-tarkistusta
    if (email.empty()) {
        return std::make_tuple(false, "empty");
    }
    
    // Tarkista, että @-merkki on olemassa
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos) {
        return std::make_tuple(false, "no_at_symbol");
    }
    
    // Tarkista, että on vain yksi @-merkki
    if (email.find('@', at_pos + 1) != std::string::npos) {
        return std::make_tuple(false, "multiple_at_symbols");
    }
    
    // Tarkista, että @ ei ole ensimmäinen tai viimeinen merkki
    if (at_pos == 0 || at_pos == email.length() - 1) {
        return std::make_tuple(false, "at_at_edge");
    }
    
    // Erota paikallinen osa ja verkkotunnus
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // Tarkista, että paikallinen osa ja verkkotunnus eivät ole tyhjiä
    if (local_part.empty() || domain_part.empty()) {
        return std::make_tuple(false, "empty_local_or_domain");
    }
    
    // Tarkista, että paikallinen osa ei ala tai päätty pisteeseen
    if (local_part.front() == '.' || local_part.back() == '.') {
        return std::make_tuple(false, "local_starts_or_ends_with_dot");
    }
    
    // Tarkista, että verkkotunnus ei ala tai päätty pisteeseen
    if (domain_part.front() == '.' || domain_part.back() == '.') {
        return std::make_tuple(false, "domain_starts_or_ends_with_dot");
    }
    
    // Tarkista, että paikallisessa osassa ei ole kahta peräkkäistä pistettä
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "consecutive_dots_in_local");
    }
    
    // Tarkista, että verkkotunnuksessa ei ole kahta peräkkäistä pistettä
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "consecutive_dots_in_domain");
    }
    
    // Tarkista, että verkkotunnuksessa on vähintään yksi piste
    if (domain_part.find('.') == std::string::npos) {
        return std::make_tuple(false, "no_dot_in_domain");
    }
    
    // Tarkista, että verkkotunnuksen viimeinen osa (TLD) on vähintään 2 merkkiä pitkä
    size_t last_dot = domain_part.rfind('.');
    std::string tld = domain_part.substr(last_dot + 1);
    if (tld.length() < 2) {
        return std::make_tuple(false, "tld_too_short");
    }
    
    // Tarkista sallitut merkit paikallisessa osassa
    for (char c : local_part) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && 
            c != '.' && c != '!' && c != '#' && c != '$' && 
            c != '%' && c != '&' && c != '\'' && c != '*' && 
            c != '+' && c != '-' && c != '/' && c != '=' && 
            c != '?' && c != '^' && c != '_' && c != '`' && 
            c != '{' && c != '|' && c != '}' && c != '~') {
            return std::make_tuple(false, "invalid_char_in_local");
        }
    }
    
    // Tarkista sallitut merkit verkkotunnuksessa
    for (char c : domain_part) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && 
            c != '.' && c != '-') {
            return std::make_tuple(false, "invalid_char_in_domain");
        }
    }
    
    // Tarkista, että verkkotunnuksen osat eivät ala tai päätty väliviivaan
    size_t start = 0;
    size_t dot_pos;
    while ((dot_pos = domain_part.find('.', start)) != std::string::npos) {
        std::string domain_label = domain_part.substr(start, dot_pos - start);
        if (domain_label.empty() || 
            domain_label.front() == '-' || 
            domain_label.back() == '-') {
            return std::make_tuple(false, "domain_label_starts_or_ends_with_hyphen");
        }
        if (domain_label.length() > 63) {
            return std::make_tuple(false, "domain_label_too_long");
        }
        start = dot_pos + 1;
    }
    
    // Tarkista viimeinen verkkotunnuksen osa
    std::string last_label = domain_part.substr(start);
    if (last_label.empty() || 
        last_label.front() == '-' || 
        last_label.back() == '-') {
        return std::make_tuple(false, "last_domain_label_starts_or_ends_with_hyphen");
    }
    if (last_label.length() > 63) {
        return std::make_tuple(false, "last_domain_label_too_long");
    }
    
    // Tarkista paikallisen osan pituus (enintään 64 merkkiä)
    if (local_part.length() > 64) {
        return std::make_tuple(false, "local_part_too_long");
    }
    
    // Tarkista koko sähköpostiosoitteen pituus (enintään 254 merkkiä)
    if (email.length() > 254) {
        return std::make_tuple(false, "email_too_long");
    }
    
    // Tarkista, että verkkotunnuksen TLD sisältää vain kirjaimia
    for (char c : tld) {
        if (!std::isalpha(static_cast<unsigned char>(c))) {
            return std::make_tuple(false, "tld_contains_non_alpha");
        }
    }
    
    // Kaikki tarkistukset läpäisty - sähköpostiosoite on kelvollinen
    return std::make_tuple(true, "valid");
}