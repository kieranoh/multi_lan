#include <string>
#include <algorithm>
#include <regex>
#include <cctype>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Проверка на пустые входные данные
    if (pattern.empty() || content.empty()) {
        return false;
    }
    
    // Проверка, если шаблон длиннее контента
    if (pattern.length() > content.length()) {
        return false;
    }
    
    try {
        // Попытка интерпретировать шаблон как регулярное выражение
        std::regex regexPattern(pattern);
        return std::regex_search(content, regexPattern);
    }
    catch (const std::regex_error&) {
        // Если шаблон не является валидным регулярным выражением,
        // выполняем простое поисковое совпадение подстроки
        return content.find(pattern) != std::string::npos;
    }
    catch (...) {
        // Обработка любых других непредвиденных ошибок
        return false;
    }
}