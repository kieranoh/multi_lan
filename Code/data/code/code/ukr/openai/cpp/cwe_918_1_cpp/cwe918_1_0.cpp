#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Перевірка на пусту строку або недійсний ідентифікатор користувача
    if (user_id.empty()) {
        return ""; // Повертаємо порожній рядок, якщо user_id порожній
    }
    
    // Формуємо та повертаємо запитуваний URL
    return api_url + "/" + user_id;
}