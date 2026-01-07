#include <string>
#include <sstream>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Провірка наявності піддомену
    if (subdomain_prefix.empty() || subdomain_prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-") != std::string::npos) {
        // Якщо піддомен порожній або недійсний, повертаємо основний домен
        return "https://" + domain;
    }

    // Формуємо URL з піддоменом
    return "https://" + subdomain_prefix + "." + domain;
}