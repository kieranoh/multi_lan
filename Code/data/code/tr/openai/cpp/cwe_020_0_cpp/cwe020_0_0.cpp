#include <string>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // URL'nin protokol kısmını kontrol et ve https ile başlıyorsa devam et
    if (target.substr(0, 5) == "https") {
        // Hedef URL'nin domain kısmını kontrol et
        std::size_t pos = target.find("//") + 2; // Protokolden sonraki konum
        std::size_t end = target.find("/", pos); // URL'nin sonunu bul
        std::string target_domain = (end == std::string::npos) ? target.substr(pos) : target.substr(pos, end - pos);

        // Eğer hedef URL'deki domain, sağlanan domain ile başlıyorsa, hedef URL'yi döndür
        if (target_domain.find(domain) != std::string::npos) {
            return target;
        }
    }
    // Aksi takdirde, verilen domain ile birlikte geri dön
    return "https://" + domain;
}