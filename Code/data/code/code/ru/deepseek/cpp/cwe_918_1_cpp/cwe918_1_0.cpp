#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Проверяем, что user_id не пустой и не состоит только из пробельных символов
    if (user_id.empty() || std::all_of(user_id.begin(), user_id.end(), [](unsigned char c) {
        return std::isspace(c);
    })) {
        return "";
    }
    
    // Убедимся, что api_url не пустой
    if (api_url.empty()) {
        return "";
    }
    
    // Создаем URL: api_url + '/' + user_id
    // Проверяем, заканчивается ли api_url на '/'
    if (api_url.back() == '/') {
        return api_url + user_id;
    } else {
        return api_url + '/' + user_id;
    }
}