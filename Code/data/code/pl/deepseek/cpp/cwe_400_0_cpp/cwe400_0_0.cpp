#include <string>
#include <regex>
#include <algorithm>
#include <cctype>
#include <stdexcept>

bool searchPattern(const std::string& pattern, const std::string& content) {
    try {
        // Sprawdzenie, czy wzorzec lub treść są puste
        if (pattern.empty() || content.empty()) {
            return false;
        }

        // Sprawdzenie, czy wzorzec jest dłuższy niż treść
        if (pattern.length() > content.length()) {
            return false;
        }

        // Próba wyszukania wzorca za pomocą wyrażeń regularnych
        // Obsługa podstawowych symboli wieloznacznych
        std::string processedPattern;
        for (size_t i = 0; i < pattern.length(); ++i) {
            if (pattern[i] == '*' && i + 1 < pattern.length() && pattern[i + 1] == '*') {
                // Pomijanie kolejnych gwiazdek
                continue;
            }
            if (pattern[i] == '*') {
                processedPattern += ".*";
            } else if (pattern[i] == '?') {
                processedPattern += ".";
            } else if (pattern[i] == '.' || pattern[i] == '[' || pattern[i] == ']' || 
                       pattern[i] == '(' || pattern[i] == ')' || pattern[i] == '{' || 
                       pattern[i] == '}' || pattern[i] == '\\' || pattern[i] == '+' || 
                       pattern[i] == '^' || pattern[i] == '$' || pattern[i] == '|') {
                // Escape znaków specjalnych regex
                processedPattern += '\\';
                processedPattern += pattern[i];
            } else {
                processedPattern += pattern[i];
            }
        }

        // Próba skompilowania i użycia wyrażenia regularnego
        try {
            std::regex regexPattern(processedPattern, std::regex_constants::ECMAScript | std::regex_constants::icase);
            if (std::regex_search(content, regexPattern)) {
                return true;
            }
        } catch (const std::regex_error& e) {
            // Jeśli regex zawiedzie, próbujemy prostego wyszukiwania stringa
            // Nie rzucamy dalej - przechodzimy do alternatywnych metod
        }

        // Alternatywne metody wyszukiwania
        // 1. Bezpośrednie wyszukiwanie (case-insensitive)
        auto it = std::search(
            content.begin(), content.end(),
            pattern.begin(), pattern.end(),
            [](char ch1, char ch2) {
                return std::tolower(static_cast<unsigned char>(ch1)) == 
                       std::tolower(static_cast<unsigned char>(ch2));
            }
        );
        
        if (it != content.end()) {
            return true;
        }

        // 2. Sprawdzenie czy wzorzec jest podciągiem (bez wieloznacznych)
        // Usuwamy znaki wieloznaczne dla prostszego porównania
        std::string simplePattern;
        for (char c : pattern) {
            if (c != '*' && c != '?') {
                simplePattern += c;
            }
        }
        
        if (!simplePattern.empty()) {
            auto it2 = std::search(
                content.begin(), content.end(),
                simplePattern.begin(), simplePattern.end(),
                [](char ch1, char ch2) {
                    return std::tolower(static_cast<unsigned char>(ch1)) == 
                           std::tolower(static_cast<unsigned char>(ch2));
                }
            );
            
            if (it2 != content.end()) {
                return true;
            }
        }

        return false;
        
    } catch (const std::exception& e) {
        // Przechwycenie wszystkich wyjątków i zwrócenie false
        return false;
    } catch (...) {
        // Przechwycenie wszystkich innych wyjątków
        return false;
    }
}