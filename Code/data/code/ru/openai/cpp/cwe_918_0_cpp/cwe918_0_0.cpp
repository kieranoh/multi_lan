#include <string>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Проверяем, является ли поддомен пустым или недействительным
    if (subdomain_prefix.empty() || subdomain_prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-") != std::string::npos) {
        return "https://" + domain;
    }

    // Формируем URL с поддоменом
    return "https://" + subdomain_prefix + "." + domain;
}