#include <string>
#include <tuple>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Obrazac koji pokriva većinu valjanih email adresa prema RFC 5322 i uobičajenim praksama
    // Ovaj obrazac je prilagođen da pokrije širok spektar slučajeva uključujući i primjer abc.123@def.ghi.com.uk
    std::string pattern = 
        R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*)"  // lokalni dio
        R"(@)"                                                                       // @ simbol
        R"((?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+)"                         // domena (jedna ili više subdomena)
        R"([a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$)";                             // TLD
    
    std::regex email_regex(pattern);
    
    // Dodatne provjere koje regex možda neće uhvatiti
    if (email.empty()) {
        return std::make_tuple(false, pattern);
    }
    
    // Provjera duljine - prema RFC 5322, maksimalna duljina je 254 znaka za cijelu adresu
    // i 64 znaka za lokalni dio (prije @)
    if (email.length() > 254) {
        return std::make_tuple(false, pattern);
    }
    
    // Pronađi poziciju @ simbola
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos || at_pos == 0 || at_pos == email.length() - 1) {
        return std::make_tuple(false, pattern);
    }
    
    // Provjeri duljinu lokalnog dijela
    std::string local_part = email.substr(0, at_pos);
    if (local_part.length() > 64) {
        return std::make_tuple(false, pattern);
    }
    
    // Provjeri da lokalni dio ne počinje ili završava s točkom
    if (local_part.front() == '.' || local_part.back() == '.') {
        return std::make_tuple(false, pattern);
    }
    
    // Provjeri da nema uzastopnih točaka u lokalnom dijelu
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // Provjeri domenu
    std::string domain = email.substr(at_pos + 1);
    if (domain.empty() || domain.length() > 253) {
        return std::make_tuple(false, pattern);
    }
    
    // Provjeri da domena ne počinje ili završava s crticom ili točkom
    if (domain.front() == '-' || domain.front() == '.' || 
        domain.back() == '-' || domain.back() == '.') {
        return std::make_tuple(false, pattern);
    }
    
    // Provjeri da nema uzastopnih točaka u domeni
    if (domain.find("..") != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // Provjeri da svaki dio domene između točaka nije predugačak (max 63 znaka)
    size_t start = 0;
    size_t dot_pos;
    do {
        dot_pos = domain.find('.', start);
        std::string label = (dot_pos == std::string::npos) ? 
                           domain.substr(start) : 
                           domain.substr(start, dot_pos - start);
        
        if (label.empty() || label.length() > 63) {
            return std::make_tuple(false, pattern);
        }
        
        // Provjeri da label ne počinje ili završava s crticom
        if (label.front() == '-' || label.back() == '-') {
            return std::make_tuple(false, pattern);
        }
        
        start = dot_pos + 1;
    } while (dot_pos != std::string::npos);
    
    // Konačna provjera regexom
    bool is_valid = std::regex_match(email, email_regex);
    
    return std::make_tuple(is_valid, pattern);
}