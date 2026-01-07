#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Überprüfen, ob das Muster oder der Inhalt leer sind
    if (pattern.empty() || content.empty()) {
        return false;
    }

    // Verwenden von std::string::find, um nach dem Muster im Inhalt zu suchen
    size_t found = content.find(pattern);
    return (found != std::string::npos);
}