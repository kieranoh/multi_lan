#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    try {
        // Deseni içerikte bulmak için std::string'in find() metodunu kullanıyoruz.
        return content.find(pattern) != std::string::npos;
    } catch (...) {
        // Herhangi bir hata durumunda false döner.
        return false;
    }
}