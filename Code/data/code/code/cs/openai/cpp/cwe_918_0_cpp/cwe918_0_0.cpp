#include <string>
#include <iostream>
#include <regex>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Validace domény
    std::regex domain_regex(R"(^([a-zA-Z0-9-]+\.)+[a-zA-Z]{2,}$)");
    if (!std::regex_match(domain, domain_regex)) {
        return ""; // Vrať prázdný řetězec pro neplatnou doménu
    }

    // Kontrola prázdného prefixu subdomény
    if (subdomain_prefix.empty() || subdomain_prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-") != std::string::npos) {
        return "https://" + domain; // Pokud je prefix prázdný nebo neplatný, vrať pouze doménu
    }

    // Sestavení URL
    return "https://" + subdomain_prefix + "." + domain;
}