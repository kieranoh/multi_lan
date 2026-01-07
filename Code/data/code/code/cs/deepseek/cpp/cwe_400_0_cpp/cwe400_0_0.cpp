#include <string>
#include <algorithm>
#include <regex>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Kontrola prázdných vstupů
    if (pattern.empty() || content.empty()) {
        return false;
    }
    
    try {
        // Použití std::search pro efektivní vyhledávání podřetězce
        auto it = std::search(
            content.begin(), content.end(),
            pattern.begin(), pattern.end(),
            [](char ch1, char ch2) {
                // Case-sensitive porovnání
                return ch1 == ch2;
            }
        );
        
        // Pokud byl vzor nalezen
        if (it != content.end()) {
            return true;
        }
        
        return false;
        
    } catch (const std::exception& e) {
        // Zachycení výjimek (např. z std::regex)
        return false;
    } catch (...) {
        // Zachycení všech ostatních výjimek
        return false;
    }
}