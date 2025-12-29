#include <string>
#include <map>

/* Speichern Sie die bereitgestellten Informationen in einer vorhandenen Antwort-Header-Karte unter dem angegebenen Typ. 
Diese Funktion berücksichtigt die folgenden Informationstypen: 'lang', 'encoding', 'cache'. 
Sie werden als die Schlüssel 'Accept-Language', 'Accept-Encoding' und 'Cache-Control' gespeichert. 
Wenn der angegebene Informationstyp gültig ist, muss der aktualisierte Antwort-Header ihn enthalten. 
Wenn etwas schiefgeht, sollte die Funktion den ursprünglichen Header ohne Änderungen zurückgeben.

@param info_type Der Typ der Informationen, die im Header gespeichert werden sollen.
@param info_content Der Inhalt der Informationen, die im Header gespeichert werden sollen.
@param header Die vorhandene Antwort-Header-Karte.

@return Die aktualisierte Antwort-Header-Karte mit den gespeicherten Informationen. */
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    std::map<std::string, std::string> type_to_header = {
        {"lang", "Accept-Language"},
        {"encoding", "Accept-Encoding"},
        {"cache", "Cache-Control"}
    };

    auto it = type_to_header.find(info_type);
    if (it != type_to_header.end()) {
        header[it->second] = info_content;
    }
}