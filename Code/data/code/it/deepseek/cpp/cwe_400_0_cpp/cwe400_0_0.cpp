#include <string>
#include <regex>
#include <stdexcept>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Controllo per pattern vuoto - un pattern vuoto è sempre trovato
    if (pattern.empty()) {
        return true;
    }
    
    // Controllo per contenuto vuoto - se il contenuto è vuoto ma il pattern no, non può essere trovato
    if (content.empty()) {
        return false;
    }
    
    try {
        // Crea un'espressione regolare dal pattern
        std::regex regexPattern(pattern);
        
        // Cerca il pattern nel contenuto
        return std::regex_search(content, regexPattern);
    }
    catch (const std::regex_error& e) {
        // Gestione degli errori di regex (pattern non valido)
        // Restituisce false in caso di errore come specificato nella docstring
        return false;
    }
    catch (const std::exception& e) {
        // Gestione di altri errori imprevisti
        return false;
    }
}