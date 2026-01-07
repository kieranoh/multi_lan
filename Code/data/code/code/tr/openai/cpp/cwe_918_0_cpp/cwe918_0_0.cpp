#include <string>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Eğer alt alan adı geçersiz veya boşsa, yalnızca alan adını döndür
    if (subdomain_prefix.empty() || subdomain_prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-") != std::string::npos) {
        return "https://" + domain;
    }
    // Geçerli alt alan adı ile URL'yi oluştur
    return "https://" + subdomain_prefix + "." + domain;
}