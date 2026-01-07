#include <string>
#include <algorithm>
#include <regex>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Überprüfen auf leeres Muster (leeres Muster wird immer gefunden)
    if (pattern.empty()) {
        return true;
    }
    
    // Überprüfen auf leeren Inhalt (kann kein nicht-leeres Muster enthalten)
    if (content.empty()) {
        return false;
    }
    
    try {
        // Versuche, das Muster als regulären Ausdruck zu interpretieren
        std::regex regexPattern(pattern);
        
        // Suche nach dem Muster im Inhalt
        return std::regex_search(content, regexPattern);
    } 
    catch (const std::regex_error&) {
        // Falls das Muster kein gültiger regulärer Ausdruck ist,
        // verwende einfache String-Suche
        return content.find(pattern) != std::string::npos;
    }
    catch (...) {
        // Alle anderen Fehler abfangen
        return false;
    }
}