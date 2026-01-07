#include <map>
#include <string>
#include <algorithm>
#include <cctype>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Informazio mota balidatu
    if (info_type.empty() || info_content.empty()) {
        return; // Jatorrizko goiburua itzuli aldaketarik gabe
    }
    
    // Informazio mota zehaztu eta dagokion goiburu gakoa esleitu
    std::string header_key;
    if (info_type == "lang") {
        header_key = "Accept-Language";
    } else if (info_type == "encoding") {
        header_key = "Accept-Encoding";
    } else if (info_type == "cache") {
        header_key = "Cache-Control";
    } else {
        return; // Informazio mota baliogabea, jatorrizko goiburua itzuli
    }
    
    // Edukia balidatu (hutsik ez egoteko eta karaktere onargarriak izateko)
    bool valid_content = false;
    for (char c : info_content) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            valid_content = true;
            break;
        }
    }
    
    if (!valid_content) {
        return; // Edukia hutsa da, jatorrizko goiburua itzuli
    }
    
    // Goiburua eguneratu
    header[header_key] = info_content;
}