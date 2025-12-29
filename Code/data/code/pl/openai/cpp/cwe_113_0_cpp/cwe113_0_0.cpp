#include <map>
#include <string>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Mapowanie typów informacji na odpowiednie nagłówki
    std::map<std::string, std::string> info_map = {
        {"lang", "Accept-Language"},
        {"encoding", "Accept-Encoding"},
        {"cache", "Cache-Control"}
    };

    // Sprawdzenie, czy podany typ informacji jest ważny
    auto it = info_map.find(info_type);
    if (it != info_map.end() && !info_content.empty()) {
        // Aktualizacja nagłówka odpowiedzi
        header[it->second] = info_content;
    }
    // W przeciwnym razie, nie dokonujemy żadnych zmian w nagłówku
}