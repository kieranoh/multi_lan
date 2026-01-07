#include <string>
#include <map>
#include <algorithm>
#include <cctype>

// Вспомогательная функция для приведения строки к нижнему регистру
std::string to_lower(const std::string& str) {
    std::string lower_str = str;
    std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return lower_str;
}

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Создаем копию оригинальных заголовков на случай ошибки
    std::map<std::string, std::string> original_header = header;
    
    try {
        std::string lower_type = to_lower(info_type);
        
        // Проверяем тип информации и обновляем соответствующий заголовок
        if (lower_type == "lang") {
            header["Accept-Language"] = info_content;
        } 
        else if (lower_type == "encoding") {
            header["Accept-Encoding"] = info_content;
        } 
        else if (lower_type == "cache") {
            header["Cache-Control"] = info_content;
        } 
        else {
            // Неверный тип информации - восстанавливаем оригинальный заголовок
            header = std::move(original_header);
        }
    } 
    catch (...) {
        // При любой ошибке восстанавливаем оригинальный заголовок
        header = std::move(original_header);
    }
}