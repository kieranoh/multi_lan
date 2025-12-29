#include <string>
#include <iostream>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Kontrollera om måladressen börjar med https:// och domänen finns i måladressen
    std::string https_prefix = "https://";
    std::string domain_with_https = https_prefix + domain;

    // Kontrollera om måladressen är en del av den specificerade domänen
    if (target.find(domain_with_https) == 0 || target.find("https://" + domain) == 0) {
        return target; // Om måladressen är inom domänen, returnera måladressen
    } else {
        return domain_with_https; // Annars, returnera domänens URL
    }
}