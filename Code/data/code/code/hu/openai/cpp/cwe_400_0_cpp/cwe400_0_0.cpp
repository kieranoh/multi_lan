#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Ellenőrizzük, hogy a minta vagy a tartalom üres-e
    if (pattern.empty() || content.empty()) {
        return false;
    }
    
    // Használjuk a std::string::find függvényt a minta keresésére a tartalomban
    size_t found = content.find(pattern);
    
    // Ha a minta megtalálható, a find függvény nem tér vissza std::string::npos-szal
    return (found != std::string::npos);
}