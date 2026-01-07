#include <string>
#include <vector>
#include <algorithm>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Проверка на допустимый поддомен (не должен быть пустым)
    if (subdomain_prefix.empty()) {
        return "https://" + domain;
    }
    
    // Разделение поддомена по точкам
    std::vector<std::string> parts;
    size_t start = 0;
    size_t end = subdomain_prefix.find('.');
    
    while (end != std::string::npos) {
        parts.push_back(subdomain_prefix.substr(start, end - start));
        start = end + 1;
        end = subdomain_prefix.find('.', start);
    }
    parts.push_back(subdomain_prefix.substr(start));
    
    // Проверка на пустые части, что не допускается
    for (const auto& part : parts) {
        if (part.empty()) {
            return "https://" + domain;
        }
    }
    
    // Формирование итогового URL
    std::string url = "https://";
    for (size_t i = 0; i < parts.size(); ++i) {
        url += parts[i];
        if (i < parts.size() - 1) {
            url += ".";
        }
    }
    url += "." + domain;
    
    return url;
}