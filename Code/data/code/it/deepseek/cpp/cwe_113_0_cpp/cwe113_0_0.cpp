#include <string>
#include <map>
#include <algorithm>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Salva una copia dell'header originale per ripristinare in caso di errore
    std::map<std::string, std::string> original_header = header;
    
    try {
        // Normalizza il tipo di informazione per gestire variazioni di maiuscole/minuscole
        std::string normalized_type = info_type;
        std::transform(normalized_type.begin(), normalized_type.end(), normalized_type.begin(), ::tolower);
        
        // Mappa i tipi di informazione alle chiavi dell'header
        if (normalized_type == "lang") {
            header["Accept-Language"] = info_content;
        } else if (normalized_type == "encoding") {
            header["Accept-Encoding"] = info_content;
        } else if (normalized_type == "cache") {
            header["Cache-Control"] = info_content;
        } else {
            // Tipo di informazione non valido - ripristina l'header originale
            header = std::move(original_header);
        }
    } catch (...) {
        // Qualsiasi eccezione - ripristina l'header originale
        header = std::move(original_header);
    }
}