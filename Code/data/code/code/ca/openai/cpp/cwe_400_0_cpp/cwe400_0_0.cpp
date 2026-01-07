#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    try {
        // Comprova si el patró està en el contingut
        return content.find(pattern) != std::string::npos;
    } catch (...) {
        // Retorna fals en cas d'error
        return false;
    }
}