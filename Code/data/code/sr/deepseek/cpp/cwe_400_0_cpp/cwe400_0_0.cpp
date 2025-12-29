#include <string>
#include <algorithm>
#include <regex>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Provera da li je obrazac prazan - prazan obrazac se smatra pronađenim
    if (pattern.empty()) {
        return true;
    }
    
    // Provera da li je sadržaj prazan - ako je obrazac neprazan, ne može biti pronađen u praznom sadržaju
    if (content.empty()) {
        return false;
    }
    
    try {
        // Pokušaj da se koristi regex pretraga za fleksibilniju pretragu
        // Escape-ujemo specijalne regex karaktere u obrascu
        std::string escapedPattern;
        for (char c : pattern) {
            if (c == '\\' || c == '^' || c == '$' || c == '.' || c == '|' || 
                c == '?' || c == '*' || c == '+' || c == '(' || c == ')' || 
                c == '[' || c == ']' || c == '{' || c == '}') {
                escapedPattern += '\\';
            }
            escapedPattern += c;
        }
        
        // Kreiraj regex objekat
        std::regex regexPattern(escapedPattern, std::regex_constants::ECMAScript | std::regex_constants::icase);
        
        // Pretraži sadržaj
        return std::regex_search(content, regexPattern);
        
    } catch (const std::regex_error& e) {
        // Ako regex ne uspe (npr. nevalidan obrazac), pokušaj jednostavnu pretragu stringa
        try {
            // Pretraga bez obzira na velika/mala slova za jednostavniju upotrebu
            std::string lowerContent = content;
            std::string lowerPattern = pattern;
            
            std::transform(lowerContent.begin(), lowerContent.end(), lowerContent.begin(),
                          [](unsigned char c) { return std::tolower(c); });
            std::transform(lowerPattern.begin(), lowerPattern.end(), lowerPattern.begin(),
                          [](unsigned char c) { return std::tolower(c); });
            
            return lowerContent.find(lowerPattern) != std::string::npos;
            
        } catch (...) {
            // Ako i ovo ne uspe, vrati false
            return false;
        }
    } catch (...) {
        // Hvataj sve druge izuzetke i vrati false
        return false;
    }
}