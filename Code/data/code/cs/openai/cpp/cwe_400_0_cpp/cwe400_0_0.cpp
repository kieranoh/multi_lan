#include <string>
#include <stdexcept>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Kontrola, zda je vzor prázdný
    if (pattern.empty()) {
        throw std::invalid_argument("Pattern cannot be empty");
    }

    // Použití standardní funkce find pro vyhledání vzoru v obsahu
    return content.find(pattern) != std::string::npos;
}