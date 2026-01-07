#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Перевірка наявності пустого паттерну
    if (pattern.empty()) {
        return false;
    }
    
    // Знаходимо позицію, де перший раз з'являється паттерн у контенті
    size_t found = content.find(pattern);
    
    // Повертаємо true, якщо паттерн знайдено, інакше false
    return (found != std::string::npos);
}