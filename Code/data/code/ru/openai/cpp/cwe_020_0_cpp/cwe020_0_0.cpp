#include <string>
#include <algorithm>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Проверяем, начинается ли целевой URL с https://
    const std::string https_prefix = "https://";
    if (target.substr(0, https_prefix.size()) != https_prefix) {
        return "https://" + domain; // Если не с https, возвращаем домен с https
    }

    // Извлекаем хост из целевого URL
    std::string::size_type start = https_prefix.size();
    std::string::size_type end = target.find('/', start);
    std::string host = (end == std::string::npos) ? target.substr(start) : target.substr(start, end - start);

    // Проверяем, содержит ли хост домен
    if (host == domain || host.ends_with("." + domain)) {
        return target; // Если домен совпадает, возвращаем целевой URL
    }

    // В противном случае возвращаем домен с https
    return "https://" + domain;
}