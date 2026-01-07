#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Provjerava da li je uzorak prazan
    if (pattern.empty()) {
        return false; // Prazan uzorak ne može biti pronađen
    }

    // Pretražuje uzorak u sadržaju
    size_t position = content.find(pattern);
    
    // Vraća true ako je uzorak pronađen, inače false
    return (position != std::string::npos);
}