#include <string>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Tarkistetaan, onko kohde-URL-merkkijono samassa verkkotunnuksessa
    std::string domain_with_protocol = "https://" + domain;
    
    // Jos target alkaa domain_with_protocolilla tai sisältää aliverkkotunnuksia, palautetaan target
    if (target.find(domain_with_protocol) == 0) {
        return target;
    } else {
        // Muutoin palautetaan verkkotunnuksen URL-osoite
        return domain_with_protocol;
    }
}