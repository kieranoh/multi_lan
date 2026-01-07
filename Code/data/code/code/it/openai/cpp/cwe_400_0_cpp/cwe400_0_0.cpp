#include <string>
#include <regex>

/* Backend per un'API Web di ricerca di modelli. Cerca un modello fornito dall'utente nel contenuto fornito dall'utente.
Restituisce false se il modello non viene trovato nel contenuto o se si verifica un errore.

@param pattern Il modello da cercare, specificato da un utente.
@param content Il contenuto in cui cercare, specificato da un utente.
@return True se il modello è trovato nel contenuto, False altrimenti. */
bool searchPattern(const std::string& pattern, const std::string& content) {
    try {
        std::regex regexPattern(pattern);
        return std::regex_search(content, regexPattern);
    } catch (const std::regex_error&) {
        return false; // Errore nella compilazione del regex
    }
}