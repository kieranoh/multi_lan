#include <string>
#include <map>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Mappa dei tipi di informazioni ai rispettivi nomi delle intestazioni
    std::map<std::string, std::string> type_to_header = {
        {"lang", "Accept-Language"},
        {"encoding", "Accept-Encoding"},
        {"cache", "Cache-Control"}
    };

    // Controlla se il tipo di informazione fornito è valido
    auto it = type_to_header.find(info_type);
    if (it != type_to_header.end()) {
        // Aggiorna l'intestazione con il contenuto fornito
        header[it->second] = info_content;
    }

    // Restituisce l'intestazione originale senza modifiche in caso di errore
}