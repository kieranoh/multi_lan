#include <map>
#include <string>
#include <algorithm>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Tarkistetaan, että info_type ja info_content eivät ole tyhjiä
    if (info_type.empty() || info_content.empty()) {
        return; // Palautetaan alkuperäinen header ilman muutoksia
    }
    
    // Muunnetaan info_type pieniksi kirjaimiksi vertailua varten
    std::string type_lower = info_type;
    std::transform(type_lower.begin(), type_lower.end(), type_lower.begin(), ::tolower);
    
    // Tarkistetaan info_type ja asetetaan vastaava header-avain
    std::string header_key;
    
    if (type_lower == "lang") {
        header_key = "Accept-Language";
    } else if (type_lower == "encoding") {
        header_key = "Accept-Encoding";
    } else if (type_lower == "cache") {
        header_key = "Cache-Control";
    } else {
        return; // Tuntematon info_type, palautetaan alkuperäinen header
    }
    
    // Tallennetaan tai päivitetään header-avain annetulla sisällöllä
    header[header_key] = info_content;
}