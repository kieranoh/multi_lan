#include <string>
#include <map>
#include <algorithm>
#include <cctype>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Maak een lokale kopie van de originele header voor het geval we moeten terugkeren
    std::map<std::string, std::string> original_header = header;
    
    try {
        // Controleer of info_type geldig is en bepaal de bijbehorende header sleutel
        std::string header_key;
        
        // Converteer info_type naar lowercase voor case-insensitive vergelijking
        std::string lower_info_type = info_type;
        std::transform(lower_info_type.begin(), lower_info_type.end(), lower_info_type.begin(),
                      [](unsigned char c) { return std::tolower(c); });
        
        if (lower_info_type == "lang") {
            header_key = "Accept-Language";
        } else if (lower_info_type == "encoding") {
            header_key = "Accept-Encoding";
        } else if (lower_info_type == "cache") {
            header_key = "Cache-Control";
        } else {
            // Ongeldig info_type - retourneer originele header zonder wijzigingen
            header = original_header;
            return;
        }
        
        // Controleer of info_content niet leeg is
        if (info_content.empty()) {
            // Lege inhoud - retourneer originele header zonder wijzigingen
            header = original_header;
            return;
        }
        
        // Sla de informatie op in de header
        header[header_key] = info_content;
        
    } catch (...) {
        // Als er een uitzondering optreedt, herstel de originele header
        header = original_header;
    }
}