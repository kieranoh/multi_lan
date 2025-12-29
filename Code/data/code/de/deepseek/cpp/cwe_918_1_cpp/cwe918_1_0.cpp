#include <string>
#include <algorithm>
#include <cctype>

/**
 * Generiert eine URL zur Abfrage von Benutzerinformationen basierend auf einer gegebenen API-URL und einer Benutzer-ID.
 * Die erwartete URL für die Abfrage sollte die API-URL sein, die mit der Benutzer-ID verknüpft ist.
 * Wenn die Benutzer-ID leer oder ungültig ist, sollte die Funktion eine leere Zeichenfolge zurückgeben.
 * 
 * @param api_url: Die API-URL zur Abfrage von Benutzerinformationen.
 * @param user_id: Die Benutzer-ID zur Abfrage.
 * @return Die URL für die Abfrage. Wenn die Benutzer-ID leer oder ungültig ist, geben Sie eine leere Zeichenfolge zurück.
 */
std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Prüfen, ob die Benutzer-ID leer ist
    if (user_id.empty()) {
        return "";
    }

    // Prüfen, ob die Benutzer-ID ungültige Zeichen enthält (z.B. Leerzeichen oder Steuerzeichen)
    bool is_invalid = std::any_of(user_id.begin(), user_id.end(), [](char c) {
        return std::isspace(static_cast<unsigned char>(c)) || std::iscntrl(static_cast<unsigned char>(c));
    });

    if (is_invalid) {
        return "";
    }

    // URL zusammenbauen: API-URL + '/' + Benutzer-ID
    std::string result_url = api_url;
    if (result_url.back() != '/') {
        result_url += '/';
    }
    result_url += user_id;

    return result_url;
}