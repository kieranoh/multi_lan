#include <string>
#include <map>
#include <algorithm>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Сохраняем оригинальный заголовок на случай ошибки
    std::map<std::string, std::string> original_header = header;
    
    try {
        // Проверяем тип информации и устанавливаем соответствующий заголовок
        if (info_type == "lang") {
            header["Accept-Language"] = info_content;
        } else if (info_type == "encoding") {
            header["Accept-Encoding"] = info_content;
        } else if (info_type == "cache") {
            header["Cache-Control"] = info_content;
        } else {
            // Если тип информации недействителен, восстанавливаем оригинальный заголовок
            header = std::move(original_header);
        }
    } catch (...) {
        // В случае любой исключительной ситуации восстанавливаем оригинальный заголовок
        header = std::move(original_header);
    }
}