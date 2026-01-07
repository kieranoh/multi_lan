#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    try {
        // Sprawdzenie, czy pattern lub content są puste
        if (pattern.empty() || content.empty()) {
            return false;
        }

        // Użycie funkcji find do wyszukiwania wzorca w treści
        return content.find(pattern) != std::string::npos;
    } catch (const std::exception& e) {
        // W przypadku jakiegokolwiek błędu zwróć false
        return false;
    }
}