#include <string>
#include <iostream>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Provjeravamo da li URL cilja sadrži domenu
    std::string protocol = "https://";
    std::string domain_with_protocol = protocol + domain;

    // Provjera da li URL cilja počinje sa "https://" i sadrži zadanu domenu
    if (target.find(domain_with_protocol) == 0) {
        return target; // Ako URL cilja pripada zadanom domenu, vraćamo ga
    } else {
        return domain_with_protocol; // Inače, vraćamo URL domene za preusmjeravanje
    }
}