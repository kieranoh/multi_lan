#include <string>
#include <map>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Mapa pro mapování typů informací na odpovídající hlavičky
    std::map<std::string, std::string> info_map = {
        {"lang", "Accept-Language"},
        {"encoding", "Accept-Encoding"},
        {"cache", "Cache-Control"}
    };

    // Zkontrolujeme, zda je zadaný typ informací platný
    auto it = info_map.find(info_type);
    if (it != info_map.end()) {
        // Uložení obsahu do hlavičky s použitím odpovídajícího klíče
        header[it->second] = info_content;
    }
    // Pokud typ není platný, hlavička zůstává nezměněna
}