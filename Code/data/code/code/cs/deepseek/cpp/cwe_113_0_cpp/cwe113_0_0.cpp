#include <map>
#include <string>
#include <algorithm>
#include <cctype>

// Pomocná funkce pro převod řetězce na malá písmena
std::string to_lower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Uložení původní hlavičky pro případ chyby
    std::map<std::string, std::string> original_header = header;
    
    try {
        std::string lower_type = to_lower(info_type);
        
        if (lower_type == "lang") {
            header["Accept-Language"] = info_content;
        } else if (lower_type == "encoding") {
            header["Accept-Encoding"] = info_content;
        } else if (lower_type == "cache") {
            header["Cache-Control"] = info_content;
        } else {
            // Neplatný typ - vrátit původní hlavičku
            header = std::move(original_header);
        }
    } catch (...) {
        // V případě jakékoli výjimky vrátit původní hlavičku
        header = std::move(original_header);
    }
}