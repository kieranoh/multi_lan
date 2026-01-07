#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    try {
        return content.find(pattern) != std::string::npos;
    } catch (const std::exception& e) {
        return false; // En caso de cualquier error, devuelve falso
    }
}