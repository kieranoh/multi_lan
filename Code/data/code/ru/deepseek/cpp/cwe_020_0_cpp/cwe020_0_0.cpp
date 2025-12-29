#include <string>
#include <algorithm>
#include <cctype>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Проверяем, начинается ли target с "https://"
    std::string https_prefix = "https://";
    if (target.find(https_prefix) != 0) {
        // Если не начинается с https://, возвращаем домен с https://
        return https_prefix + domain;
    }

    // Извлекаем хост из target
    std::string target_without_protocol = target.substr(https_prefix.length());
    size_t slash_pos = target_without_protocol.find('/');
    std::string target_host = (slash_pos == std::string::npos) 
        ? target_without_protocol 
        : target_without_protocol.substr(0, slash_pos);

    // Проверяем, заканчивается ли target_host на domain
    // Сравниваем без учета регистра
    auto case_insensitive_compare = [](char a, char b) {
        return std::tolower(static_cast<unsigned char>(a)) == 
               std::tolower(static_cast<unsigned char>(b));
    };

    // Проверяем, заканчивается ли target_host на domain
    if (target_host.length() >= domain.length()) {
        std::string target_host_end = target_host.substr(target_host.length() - domain.length());
        if (std::equal(target_host_end.begin(), target_host_end.end(), 
                       domain.begin(), domain.end(), case_insensitive_compare)) {
            // Проверяем, что домен либо точно совпадает, либо предшествует точке
            if (target_host.length() == domain.length() || 
                target_host[target_host.length() - domain.length() - 1] == '.') {
                return target;
            }
        }
    }

    // Если не в домене, возвращаем домен с https://
    return https_prefix + domain;
}