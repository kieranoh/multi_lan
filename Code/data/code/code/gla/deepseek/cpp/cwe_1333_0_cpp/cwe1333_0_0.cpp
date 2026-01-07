#include <tuple>
#include <string>
#include <regex>
#include <algorithm>
#include <cctype>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Leere E-Mail-Adresse
    if (email.empty()) {
        return {false, "E-Mail-Adresse darf nicht leer sein"};
    }
    
    // Maximale Länge gemäß RFC 5321
    if (email.length() > 254) {
        return {false, "E-Mail-Adresse darf maximal 254 Zeichen lang sein"};
    }
    
    // Mindestens ein @-Symbol vorhanden
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos) {
        return {false, "E-Mail-Adresse muss ein '@'-Symbol enthalten"};
    }
    
    // Nur ein @-Symbol erlaubt
    if (email.find('@', at_pos + 1) != std::string::npos) {
        return {false, "E-Mail-Adresse darf nur ein '@'-Symbol enthalten"};
    }
    
    // Lokaler Teil (vor @) und Domain-Teil (nach @) extrahieren
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // Lokaler Teil darf nicht leer sein
    if (local_part.empty()) {
        return {false, "Lokaler Teil (vor '@') darf nicht leer sein"};
    }
    
    // Lokaler Teil darf nicht länger als 64 Zeichen sein (RFC 5321)
    if (local_part.length() > 64) {
        return {false, "Lokaler Teil darf maximal 64 Zeichen lang sein"};
    }
    
    // Domain-Teil darf nicht leer sein
    if (domain_part.empty()) {
        return {false, "Domain-Teil (nach '@') darf nicht leer sein"};
    }
    
    // Domain-Teil darf nicht mit oder auf einem Punkt beginnen/enden
    if (domain_part.front() == '.' || domain_part.back() == '.') {
        return {false, "Domain-Teil darf nicht mit einem Punkt beginnen oder enden"};
    }
    
    // Keine aufeinanderfolgenden Punkte im Domain-Teil
    if (domain_part.find("..") != std::string::npos) {
        return {false, "Domain-Teil darf keine aufeinanderfolgenden Punkte enthalten"};
    }
    
    // Domain-Teil in Labels aufteilen
    std::vector<std::string> domain_labels;
    size_t start = 0;
    size_t end = domain_part.find('.');
    
    while (end != std::string::npos) {
        std::string label = domain_part.substr(start, end - start);
        if (label.empty()) {
            return {false, "Domain-Label darf nicht leer sein"};
        }
        domain_labels.push_back(label);
        start = end + 1;
        end = domain_part.find('.', start);
    }
    
    // Letztes Label hinzufügen
    std::string last_label = domain_part.substr(start);
    if (last_label.empty()) {
        return {false, "Letztes Domain-Label darf nicht leer sein"};
    }
    domain_labels.push_back(last_label);
    
    // Jedes Domain-Label überprüfen
    for (const auto& label : domain_labels) {
        // Label-Länge (1-63 Zeichen)
        if (label.length() < 1 || label.length() > 63) {
            return {false, "Jedes Domain-Label muss 1-63 Zeichen lang sein"};
        }
        
        // Label darf nicht mit oder auf einem Bindestrich beginnen/enden
        if (label.front() == '-' || label.back() == '-') {
            return {false, "Domain-Label darf nicht mit einem Bindestrich beginnen oder enden"};
        }
        
        // Nur erlaubte Zeichen in Labels: Buchstaben, Ziffern, Bindestriche
        for (char c : label) {
            if (!std::isalnum(static_cast<unsigned char>(c)) && c != '-') {
                return {false, "Domain-Label darf nur Buchstaben, Ziffern und Bindestriche enthalten"};
            }
        }
    }
    
    // Top-Level-Domain (letztes Label) muss mindestens 2 Zeichen haben
    if (domain_labels.back().length() < 2) {
        return {false, "Top-Level-Domain muss mindestens 2 Zeichen lang sein"};
    }
    
    // Top-Level-Domain darf nur Buchstaben enthalten
    for (char c : domain_labels.back()) {
        if (!std::isalpha(static_cast<unsigned char>(c))) {
            return {false, "Top-Level-Domain darf nur Buchstaben enthalten"};
        }
    }
    
    // Lokalen Teil auf gültige Zeichen überprüfen
    // Erlaubt: A-Z, a-z, 0-9, !#$%&'*+-/=?^_`{|}~. und Punkte (aber nicht aufeinanderfolgend oder am Anfang/Ende)
    
    // Lokaler Teil darf nicht mit oder auf einem Punkt beginnen/enden
    if (local_part.front() == '.' || local_part.back() == '.') {
        return {false, "Lokaler Teil darf nicht mit einem Punkt beginnen oder enden"};
    }
    
    // Keine aufeinanderfolgenden Punkte im lokalen Teil
    if (local_part.find("..") != std::string::npos) {
        return {false, "Lokaler Teil darf keine aufeinanderfolgenden Punkte enthalten"};
    }
    
    // Gültige Zeichen im lokalen Teil überprüfen
    bool in_quotes = false;
    bool escape_next = false;
    
    for (size_t i = 0; i < local_part.length(); ++i) {
        char c = local_part[i];
        
        if (escape_next) {
            escape_next = false;
            continue;
        }
        
        if (c == '"') {
            in_quotes = !in_quotes;
            continue;
        }
        
        if (in_quotes) {
            if (c == '\\') {
                escape_next = true;
            }
            // In Anführungszeichen sind fast alle Zeichen erlaubt
            continue;
        }
        
        // Außerhalb von Anführungszeichen
        if (std::isalnum(static_cast<unsigned char>(c))) {
            continue;
        }
        
        // Erlaubte Sonderzeichen außerhalb von Anführungszeichen
        std::string allowed_special = "!#$%&'*+-/=?^_`{|}~.";
        if (allowed_special.find(c) != std::string::npos) {
            continue;
        }
        
        return {false, "Lokaler Teil enthält ungültige Zeichen"};
    }
    
    // Wenn Anführungszeichen geöffnet wurden, müssen sie auch geschlossen werden
    if (in_quotes) {
        return {false, "Nicht geschlossene Anführungszeichen im lokalen Teil"};
    }
    
    // Internationalisierte Domain-Namen (IDN) in Punycode-Form akzeptieren
    // Punycode beginnt mit "xn--"
    for (size_t i = 0; i < domain_labels.size(); ++i) {
        const auto& label = domain_labels[i];
        if (label.length() > 4 && label.substr(0, 4) == "xn--") {
            // Punycode-Validierung: nach "xn--" müssen gültige Punycode-Zeichen folgen
            std::string punycode_part = label.substr(4);
            for (char pc : punycode_part) {
                if (!std::isalnum(static_cast<unsigned char>(pc)) && pc != '-') {
                    return {false, "Ungültige Punycode-Zeichen in Domain"};
                }
            }
        }
    }
    
    // Erfolgreiche Validierung
    return {true, "E-Mail-Adresse ist gültig"};
}