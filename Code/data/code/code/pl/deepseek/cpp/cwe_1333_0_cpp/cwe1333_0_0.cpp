#include <iostream>
#include <string>
#include <tuple>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Wzór 1: Podstawowa walidacja zgodna z RFC 5322 (bardziej restrykcyjna)
    std::string pattern1 = R"(^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$)";
    
    // Wzór 2: Bardziej liberalny, akceptujący adresy z podkreśleniami w domenie i dłuższe TLD
    std::string pattern2 = R"(^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*\.[a-zA-Z]{2,}$)";
    
    // Wzór 3: Najbardziej liberalny - akceptuje międzynarodowe nazwy domen (IDN) i dłuższe TLD
    std::string pattern3 = R"(^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$)";
    
    // Wzór 4: Akceptuje adresy z wieloma subdomenami (jak w przykładzie abc.123@def.ghi.com.uk)
    std::string pattern4 = R"(^[a-zA-Z0-9][a-zA-Z0-9._%+-]*@(?:[a-zA-Z0-9-]+\.)+[a-zA-Z]{2,}(?:\.[a-zA-Z]{2,})?$)";
    
    // Wzór 5: Najbardziej kompletny - łączy różne przypadki
    std::string pattern5 = R"(^[a-zA-Z0-9][a-zA-Z0-9._%+-]{0,63}@(?:[a-zA-Z0-9-]{1,63}\.){1,}[a-zA-Z]{2,63}(?:\.[a-zA-Z]{2,63})?$)";
    
    // Lista wzorców do testowania w kolejności od najbardziej do najmniej restrykcyjnych
    std::vector<std::pair<std::string, std::string>> patterns = {
        {"RFC 5322 compatible", pattern1},
        {"Extended TLD", pattern2},
        {"International domains", pattern3},
        {"Multiple subdomains", pattern4},
        {"Comprehensive", pattern5}
    };
    
    // Sprawdź podstawowe warunki przed użyciem regex
    if (email.empty() || email.length() > 254) {  // RFC 5321 określa maksymalną długość 254 znaków
        return std::make_tuple(false, "Invalid length");
    }
    
    // Sprawdź obecność dokładnie jednego znaku '@'
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos || at_pos == 0 || at_pos == email.length() - 1) {
        return std::make_tuple(false, "Missing or misplaced @");
    }
    
    // Sprawdź czy nie ma wielu '@'
    if (std::count(email.begin(), email.end(), '@') != 1) {
        return std::make_tuple(false, "Multiple @ symbols");
    }
    
    // Podziel na część lokalną i domenową
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // Sprawdź długość części lokalnej (RFC 5321: maksymalnie 64 znaki)
    if (local_part.length() > 64) {
        return std::make_tuple(false, "Local part too long");
    }
    
    // Sprawdź czy część lokalna nie zaczyna się ani nie kończy kropką
    if (local_part.front() == '.' || local_part.back() == '.') {
        return std::make_tuple(false, "Local part starts or ends with dot");
    }
    
    // Sprawdź czy nie ma dwóch kropek pod rząd w części lokalnej
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "Consecutive dots in local part");
    }
    
    // Sprawdź czy domena nie jest pusta
    if (domain_part.empty()) {
        return std::make_tuple(false, "Empty domain");
    }
    
    // Sprawdź czy domena nie zaczyna się ani nie kończy kropką
    if (domain_part.front() == '.' || domain_part.back() == '.') {
        return std::make_tuple(false, "Domain starts or ends with dot");
    }
    
    // Sprawdź czy nie ma dwóch kropek pod rząd w domenie
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "Consecutive dots in domain");
    }
    
    // Sprawdź czy domena ma przynajmniej jedną kropkę
    if (domain_part.find('.') == std::string::npos) {
        return std::make_tuple(false, "No dot in domain");
    }
    
    // Sprawdź czy ostatnia część domeny (TLD) ma przynajmniej 2 znaki
    size_t last_dot = domain_part.find_last_of('.');
    std::string tld = domain_part.substr(last_dot + 1);
    if (tld.length() < 2) {
        return std::make_tuple(false, "TLD too short");
    }
    
    // Przetestuj wszystkie wzorce w kolejności
    for (const auto& [pattern_name, pattern_str] : patterns) {
        try {
            std::regex email_regex(pattern_str, std::regex_constants::ECMAScript | std::regex_constants::icase);
            if (std::regex_match(email, email_regex)) {
                return std::make_tuple(true, pattern_name);
            }
        } catch (const std::regex_error& e) {
            // Kontynuuj z następnym wzorcem w przypadku błędu regex
            continue;
        }
    }
    
    // Jeśli żaden wzorzec nie pasuje, spróbuj bardziej szczegółowej walidacji
    // Walidacja znaków w części lokalnej
    for (char c : local_part) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && 
            c != '.' && c != '!' && c != '#' && c != '$' && c != '%' && 
            c != '&' && c != '\'' && c != '*' && c != '+' && c != '-' && 
            c != '/' && c != '=' && c != '?' && c != '^' && c != '_' && 
            c != '`' && c != '{' && c != '|' && c != '}' && c != '~') {
            return std::make_tuple(false, "Invalid character in local part");
        }
    }
    
    // Walidacja domeny
    for (char c : domain_part) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '.' && c != '-') {
            return std::make_tuple(false, "Invalid character in domain");
        }
    }
    
    // Sprawdź czy każda część domeny ma odpowiednią długość (1-63 znaków)
    size_t start = 0;
    size_t end = domain_part.find('.');
    while (end != std::string::npos) {
        std::string domain_label = domain_part.substr(start, end - start);
        if (domain_label.empty() || domain_label.length() > 63) {
            return std::make_tuple(false, "Invalid domain label length");
        }
        start = end + 1;
        end = domain_part.find('.', start);
    }
    
    // Sprawdź ostatnią część domeny
    std::string last_label = domain_part.substr(start);
    if (last_label.empty() || last_label.length() > 63) {
        return std::make_tuple(false, "Invalid TLD length");
    }
    
    // Jeśli wszystkie podstawowe testy przeszły, ale regex nie, zwróć częściowy sukces
    return std::make_tuple(true, "Basic validation passed (regex failed)");
}