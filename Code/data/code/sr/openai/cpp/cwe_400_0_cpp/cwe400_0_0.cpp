#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Proveravamo da li je obrazac prazan
    if (pattern.empty()) {
        return false; // Vraćamo false ako je obrazac prazan
    }

    // Koristimo std::string::find() da tražimo obrazac u sadržaju
    size_t found = content.find(pattern);
    
    // Ako je obrazac pronađen, found neće biti std::string::npos
    return found != std::string::npos;
}