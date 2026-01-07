#include <string>
#include <algorithm>
#include <cctype>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Hantera tomma strängar: tomt mönster hittas alltid (enligt konvention)
    if (pattern.empty()) {
        return true;
    }
    
    // Om innehållet är tomt kan vi inte hitta något mönster (förutom tomt mönster)
    if (content.empty()) {
        return false;
    }
    
    // Använd std::search för att söka efter mönstret i innehållet
    auto it = std::search(
        content.begin(), content.end(),
        pattern.begin(), pattern.end()
    );
    
    // Returnera true om mönstret hittades, false annars
    return it != content.end();
}