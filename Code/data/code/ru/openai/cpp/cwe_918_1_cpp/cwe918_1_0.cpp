#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Проверяем, является ли user_id пустым или недействительным
    if (user_id.empty()) {
        return ""; // Возвращаем пустую строку
    }
    // Генерируем и возвращаем полный URL
    return api_url + "/" + user_id;
}