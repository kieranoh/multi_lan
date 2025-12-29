#include <tuple>
#include <string>
#include <cctype>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // 1. Helbide hutsa egiaztatu
    if (email.empty()) {
        return std::make_tuple(false, "Posta helbidea hutsa dago");
    }
    
    // 2. @ ikurraren presentzia egiaztatu
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos) {
        return std::make_tuple(false, "@ ikurra falta da");
    }
    
    // 3. @ ikurraren posizioa egiaztatu (ez lehena, ez azkena)
    if (at_pos == 0) {
        return std::make_tuple(false, "@ ikurra ezin da lehen karakterea izan");
    }
    if (at_pos == email.length() - 1) {
        return std::make_tuple(false, "@ ikurra ezin da azken karakterea izan");
    }
    
    // 4. @ ikurraren bikoiztea egiaztatu
    if (email.find('@', at_pos + 1) != std::string::npos) {
        return std::make_tuple(false, "@ ikur bat baino gehiago dago");
    }
    
    // 5. Toki-izenaren eta domeinuaren zatitan banatu
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // 6. Toki-izena hutsa egiaztatu
    if (local_part.empty()) {
        return std::make_tuple(false, "Toki-izena hutsa dago");
    }
    
    // 7. Domeinua hutsa egiaztatu
    if (domain_part.empty()) {
        return std::make_tuple(false, "Domeinua hutsa dago");
    }
    
    // 8. Toki-izenaren karaktere baliogabeak egiaztatu
    for (size_t i = 0; i < local_part.length(); ++i) {
        char c = local_part[i];
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '.' && c != '_' && c != '-' && c != '+') {
            return std::make_tuple(false, "Toki-izenean karaktere baliogabeak daude");
        }
    }
    
    // 9. Toki-izenaren puntuazio jarraitua egiaztatu
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "Toki-izenean puntuazio jarraitua dago");
    }
    
    // 10. Toki-izenaren hasiera/amaiera puntua egiaztatu
    if (local_part.front() == '.' || local_part.back() == '.') {
        return std::make_tuple(false, "Toki-izena ezin da puntuarekin hasi edo amaitu");
    }
    
    // 11. Domeinuaren karaktere baliogabeak egiaztatu
    for (size_t i = 0; i < domain_part.length(); ++i) {
        char c = domain_part[i];
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '.' && c != '-') {
            return std::make_tuple(false, "Domeinuan karaktere baliogabeak daude");
        }
    }
    
    // 12. Domeinuaren puntuazio jarraitua egiaztatu
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "Domeinuan puntuazio jarraitua dago");
    }
    
    // 13. Domeinuaren hasiera/amaiera puntua edo marra egiaztatu
    if (domain_part.front() == '.' || domain_part.front() == '-' ||
        domain_part.back() == '.' || domain_part.back() == '-') {
        return std::make_tuple(false, "Domeinua ezin da puntuarekin edo marrarekin hasi edo amaitu");
    }
    
    // 14. Domeinuaren azken zatia egiaztatu (gutxienez 2 karaktere)
    size_t last_dot = domain_part.find_last_of('.');
    if (last_dot == std::string::npos) {
        return std::make_tuple(false, "Domeinuak gutxienez puntu bat izan behar du");
    }
    
    std::string last_part = domain_part.substr(last_dot + 1);
    if (last_part.length() < 2) {
        return std::make_tuple(false, "Domeinuaren azken zatia gutxienez 2 karaktere izan behar ditu");
    }
    
    // 15. Domeinuaren azken zatiko karaktereak egiaztatu (letrak bakarrik)
    for (char c : last_part) {
        if (!std::isalpha(static_cast<unsigned char>(c))) {
            return std::make_tuple(false, "Domeinuaren azken zatia letraz soilik osatuta egon behar da");
        }
    }
    
    // 16. Luzera maximoa egiaztatu (RFC 5321)
    if (email.length() > 254) {
        return std::make_tuple(false, "Posta helbidea luzeegia da (254 karaktere gehienez)");
    }
    
    // 17. Toki-izenaren luzera maximoa egiaztatu (RFC 5321)
    if (local_part.length() > 64) {
        return std::make_tuple(false, "Toki-izena luzeegia da (64 karaktere gehienez)");
    }
    
    // 18. Domeinuaren luzera maximoa egiaztatu (RFC 1035)
    if (domain_part.length() > 253) {
        return std::make_tuple(false, "Domeinua luzeegia da (253 karaktere gehienez)");
    }
    
    // 19. Domeinuaren zatien luzera egiaztatu (RFC 1035)
    size_t start = 0;
    while (start < domain_part.length()) {
        size_t dot_pos = domain_part.find('.', start);
        if (dot_pos == std::string::npos) {
            dot_pos = domain_part.length();
        }
        
        size_t part_length = dot_pos - start;
        if (part_length > 63) {
            return std::make_tuple(false, "Domeinuaren zati bat luzeegia da (63 karaktere gehienez)");
        }
        
        start = dot_pos + 1;
    }
    
    return std::make_tuple(true, "Posta helbidea baliozkoa da");
}