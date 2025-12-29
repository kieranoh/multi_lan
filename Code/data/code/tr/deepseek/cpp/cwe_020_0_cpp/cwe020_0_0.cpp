#include <string>
#include <algorithm>
#include <cctype>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Boş girişleri kontrol et
    if (target.empty() || domain.empty()) {
        return "https://" + domain;
    }
    
    // Hedef URL'nin "https://" ile başlayıp başlamadığını kontrol et
    std::string https_prefix = "https://";
    if (target.find(https_prefix) != 0) {
        return "https://" + domain;
    }
    
    // "https://" sonrasındaki kısmı al
    std::string target_without_protocol = target.substr(https_prefix.length());
    
    // İlk '/' karakterini bul (varsa)
    size_t slash_pos = target_without_protocol.find('/');
    
    // Alan adı kısmını çıkar
    std::string target_domain;
    if (slash_pos != std::string::npos) {
        target_domain = target_without_protocol.substr(0, slash_pos);
    } else {
        target_domain = target_without_protocol;
    }
    
    // Alan adlarını karşılaştır
    // Hedef alan adının verilen alan adı ile bitip bitmediğini kontrol et
    if (target_domain.length() >= domain.length()) {
        // Hedef alan adının son kısmını al
        std::string target_end = target_domain.substr(target_domain.length() - domain.length());
        
        // Eğer tam eşleşme varsa veya hedef alan adı verilen alan adı ile bitiyorsa
        // ve öncesinde nokta varsa veya tam eşleşiyorsa
        if (target_end == domain) {
            // Tam eşleşme veya alt alan adı kontrolü
            if (target_domain.length() == domain.length() || 
                target_domain[target_domain.length() - domain.length() - 1] == '.') {
                return target;
            }
        }
    }
    
    // Eşleşme yoksa, verilen alan adına geri dön
    return "https://" + domain;
}