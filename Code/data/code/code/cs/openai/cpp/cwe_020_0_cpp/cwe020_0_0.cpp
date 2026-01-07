#include <string>
#include <iostream>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Zkontrolujeme, zda je cílový URL platný a zda odpovídá doméně
    std::string protocol = "https://";
    std::string target_domain;

    // Najdeme doménu cílového URL
    size_t pos = target.find("://");
    if (pos == std::string::npos) {
        return protocol + domain; // Pokud není protokol, vrátíme doménu
    }
    
    pos += 3; // Přeskočíme "://"
    size_t end_pos = target.find('/', pos);
    if (end_pos == std::string::npos) {
        target_domain = target.substr(pos); // Celá doména bez cesty
    } else {
        target_domain = target.substr(pos, end_pos - pos); // Doména s cestou
    }

    // Zkontrolujeme, zda se cílová doména shoduje s požadovanou doménou
    if (target_domain == domain || target_domain.substr(target_domain.find(domain)) == domain) {
        return target; // Pokud se domény shodují, vrátíme cílový URL
    } else {
        return protocol + domain; // Jinak vrátíme doménový URL
    }
}