#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Temizlenmiş alan adı ve alt alan adı için değişkenler
    std::string clean_domain = domain;
    std::string clean_subdomain = subdomain_prefix;
    
    // Boşlukları kaldır
    auto remove_whitespace = [](std::string& str) {
        str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
    };
    
    remove_whitespace(clean_domain);
    remove_whitespace(clean_subdomain);
    
    // Alan adı boşsa, boş string döndür
    if (clean_domain.empty()) {
        return "";
    }
    
    // Alt alan adı boşsa veya sadece noktalardan oluşuyorsa, sadece alan adını kullan
    if (clean_subdomain.empty() || 
        std::all_of(clean_subdomain.begin(), clean_subdomain.end(), [](char c) { return c == '.'; })) {
        return "https://" + clean_domain;
    }
    
    // Alt alan adını temizle: baştaki ve sondaki noktaları kaldır
    size_t start = clean_subdomain.find_first_not_of('.');
    size_t end = clean_subdomain.find_last_not_of('.');
    
    if (start == std::string::npos) {  // Sadece noktalardan oluşuyorsa
        return "https://" + clean_domain;
    }
    
    std::string trimmed_subdomain = clean_subdomain.substr(start, end - start + 1);
    
    // URL'yi oluştur
    std::string url = "https://" + trimmed_subdomain + "." + clean_domain;
    
    return url;
}