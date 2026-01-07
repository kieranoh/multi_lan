#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Egiaztatu parametro hutsak
    if (target.empty() || domain.empty()) {
        return "https://" + domain;
    }
    
    // Egiaztatu target-ak "https://" hasten duen
    std::string https_prefix = "https://";
    if (target.find(https_prefix) != 0) {
        return "https://" + domain;
    }
    
    // Kendu protokoloa target-etik domeinua konparatzeko
    std::string target_without_protocol = target.substr(https_prefix.length());
    
    // Bilatu lehenengo '/' karakterea domeinua eta bidea bereizteko
    size_t slash_pos = target_without_protocol.find('/');
    std::string target_domain;
    
    if (slash_pos == std::string::npos) {
        // Ez dago '/', beraz, string osoa domeinua da
        target_domain = target_without_protocol;
    } else {
        // Hartu '/' karakterearen aurretik dagoena domeinu gisa
        target_domain = target_without_protocol.substr(0, slash_pos);
    }
    
    // Konparatu domeinuak (case-insensitive)
    auto strings_equal_ignore_case = [](const std::string& a, const std::string& b) -> bool {
        if (a.length() != b.length()) {
            return false;
        }
        return std::equal(a.begin(), a.end(), b.begin(),
                         [](char c1, char c2) {
                             return std::tolower(static_cast<unsigned char>(c1)) == 
                                    std::tolower(static_cast<unsigned char>(c2));
                         });
    };
    
    // Egiaztatu target_domain-ak domeinua amaieran duen
    // (adibidez: "music.example.com" "example.com"-rekin)
    if (target_domain.length() >= domain.length()) {
        // Egiaztatu target_domain-ak domeinua amaieran duen
        if (target_domain.length() == domain.length()) {
            // Luzera berdina: domeinuak berdinak izan behar dute
            if (strings_equal_ignore_case(target_domain, domain)) {
                return target;
            }
        } else {
            // target_domain luzeagoa da: domeinua amaieran egon behar du
            // Egiaztatu '.' karakterea domeinuaren aurretik
            size_t domain_start_pos = target_domain.length() - domain.length();
            if (target_domain[domain_start_pos - 1] == '.' &&
                strings_equal_ignore_case(target_domain.substr(domain_start_pos), domain)) {
                return target;
            }
        }
    }
    
    // Ez dator bat, itzuli domeinuko URL-a
    return "https://" + domain;
}