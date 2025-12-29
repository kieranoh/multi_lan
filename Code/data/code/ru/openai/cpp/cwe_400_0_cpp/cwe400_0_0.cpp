#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Проверяем, не является ли шаблон пустым
    if (pattern.empty()) {
        return false;
    }
    
    // Используем метод find для поиска шаблона в контенте
    size_t found = content.find(pattern);
    
    // Если метод find вернул значение, отличное от std::string::npos, то шаблон найден
    return found != std::string::npos;
}