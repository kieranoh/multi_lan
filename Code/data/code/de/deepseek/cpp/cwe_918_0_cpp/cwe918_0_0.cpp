#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Prüfe, ob die Subdomain leer oder ungültig ist
    bool subdomain_valid = !subdomain_prefix.empty();
    
    // Überprüfe auf ungültige Zeichen in der Subdomain
    if (subdomain_valid) {
        // Ein gültiges Subdomain-Präfix sollte nicht leer sein und keine führenden/abschließenden Punkte haben
        // sowie keine aufeinanderfolgenden Punkte enthalten
        if (subdomain_prefix.front() == '.' || subdomain_prefix.back() == '.' ||
            subdomain_prefix.find("..") != std::string::npos) {
            subdomain_valid = false;
        }
        
        // Überprüfe auf ungültige Zeichen (nur alphanumerische Zeichen, Bindestriche und Punkte erlaubt)
        for (char c : subdomain_prefix) {
            if (!std::isalnum(static_cast<unsigned char>(c)) && c != '-' && c != '.') {
                subdomain_valid = false;
                break;
            }
        }
    }
    
    // Baue die URL zusammen
    std::string url = "https://";
    
    if (subdomain_valid) {
        url += subdomain_prefix + "." + domain;
    } else {
        url += domain;
    }
    
    return url;
}