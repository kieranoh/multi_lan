#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Hilfsfunktion, um einen String in Kleinbuchstaben umzuwandeln
    auto to_lower = [](std::string str) -> std::string {
        std::transform(str.begin(), str.end(), str.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return str;
    };

    // Hilfsfunktion, um das Protokoll aus einer URL zu extrahieren
    auto extract_protocol = [](const std::string& url) -> std::string {
        size_t pos = url.find("://");
        if (pos != std::string::npos) {
            return url.substr(0, pos);
        }
        return "";
    };

    // Hilfsfunktion, um die Domain aus einer URL zu extrahieren
    auto extract_domain = [](const std::string& url) -> std::string {
        size_t start = url.find("://");
        if (start == std::string::npos) {
            start = 0;
        } else {
            start += 3; // Länge von "://"
        }
        
        size_t end = url.find('/', start);
        std::string host = (end == std::string::npos) ? 
                           url.substr(start) : 
                           url.substr(start, end - start);
        
        // Port entfernen, falls vorhanden
        size_t port_pos = host.find(':');
        if (port_pos != std::string::npos) {
            host = host.substr(0, port_pos);
        }
        
        return host;
    };

    // Ziel-URL und Domain in Kleinbuchstaben umwandeln für case-insensitive Vergleiche
    std::string target_lower = to_lower(target);
    std::string domain_lower = to_lower(domain);

    // Prüfen, ob die Ziel-URL ein gültiges Protokoll hat
    std::string target_protocol = extract_protocol(target_lower);
    if (target_protocol.empty()) {
        // Kein Protokoll gefunden, verwende die Domain-URL
        return "https://" + domain;
    }

    // Domain aus der Ziel-URL extrahieren
    std::string target_domain = extract_domain(target_lower);

    // Prüfen, ob die extrahierte Domain mit der angegebenen Domain übereinstimmt
    // oder eine Subdomain davon ist
    if (target_domain == domain_lower || 
        (target_domain.length() > domain_lower.length() + 1 &&
         target_domain.substr(target_domain.length() - domain_lower.length() - 1) == 
         "." + domain_lower)) {
        // Ziel-URL liegt innerhalb der Domain, verwende sie
        // Stelle sicher, dass das Protokoll https ist
        if (target_protocol == "https") {
            return target;
        } else {
            // Ersetze das Protokoll durch https
            size_t protocol_end = target.find("://");
            return "https" + target.substr(protocol_end);
        }
    }

    // Ziel-URL liegt nicht innerhalb der Domain, verwende die Domain-URL
    return "https://" + domain;
}