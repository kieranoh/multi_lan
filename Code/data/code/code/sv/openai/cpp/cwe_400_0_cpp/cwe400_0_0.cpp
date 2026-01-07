#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Kontrollera om mönstret är tomt
    if (pattern.empty()) {
        return false;
    }

    // Använd std::string::find för att söka efter mönstret i innehållet
    size_t found = content.find(pattern);
    
    // Returnera true om mönstret hittas, annars false
    return found != std::string::npos;
}