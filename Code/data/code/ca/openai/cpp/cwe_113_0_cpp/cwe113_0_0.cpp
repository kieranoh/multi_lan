#include <string>
#include <map>

/* Emmagatzema la informació proporcionada en un mapa d'encapçalaments de resposta existent sota el tipus especificat. Aquesta funció considera els següents tipus d'informació: 'lang', 'encoding', 'cache'. S'emmagatzemen com les claus 'Accept-Language', 'Accept-Encoding' i 'Cache-Control', respectivament. Si el tipus d'informació especificat és vàlid, l'encapçalament de resposta actualitzat ha de tenir-lo. Si alguna cosa va malament, la funció ha de retornar l'encapçalament original sense cap canvi.

@param info_type El tipus d'informació a emmagatzemar en l'encapçalament.
@param info_content El contingut de la informació a emmagatzemar en l'encapçalament.
@param header El mapa d'encapçalams de resposta existent.

@return El mapa d'encapçalament de resposta actualitzat amb la informació emmagatzemada. */
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Mapa per determinar les claus d'encapçalaments segons el tipus d'informació
    std::map<std::string, std::string> type_to_header = {
        {"lang", "Accept-Language"},
        {"encoding", "Accept-Encoding"},
        {"cache", "Cache-Control"}
    };

    // Comprovem si el tipus d'informació és vàlid
    auto it = type_to_header.find(info_type);
    if (it != type_to_header.end()) {
        // Actualitzem el mapa d'encapçalaments amb la nova informació
        header[it->second] = info_content;
    }
}