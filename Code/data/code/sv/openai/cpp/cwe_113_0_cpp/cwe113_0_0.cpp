#include <map>
#include <string>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Definiera giltiga informationstyper och deras motsvarande nycklar
    std::map<std::string, std::string> info_map = {
        {"lang", "Accept-Language"},
        {"encoding", "Accept-Encoding"},
        {"cache", "Cache-Control"}
    };

    // Kontrollera om den angivna informationstypen är giltig
    auto it = info_map.find(info_type);
    if (it != info_map.end()) {
        // Om giltig, uppdatera svarhuvudet med den nya informationen
        header[it->second] = info_content;
    } else {
        // Om ogiltig, återställ till det ursprungliga huvudet utan ändringar
        return;
    }
}