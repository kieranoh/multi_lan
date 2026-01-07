#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Controlla se l'ID utente è vuoto o non valido
    if (user_id.empty()) {
        return "";
    }
    
    // Controlla se l'ID utente contiene solo spazi bianchi
    bool all_whitespace = std::all_of(user_id.begin(), user_id.end(), [](unsigned char c) {
        return std::isspace(c);
    });
    
    if (all_whitespace) {
        return "";
    }
    
    // Rimuove gli spazi bianchi iniziali e finali dall'ID utente
    size_t start = user_id.find_first_not_of(" \t\n\r\f\v");
    size_t end = user_id.find_last_not_of(" \t\n\r\f\v");
    
    if (start == std::string::npos) {
        return ""; // Tutti spazi bianchi (già gestito sopra, ma per sicurezza)
    }
    
    std::string trimmed_user_id = user_id.substr(start, end - start + 1);
    
    // Controlla se l'ID utente tagliato è vuoto
    if (trimmed_user_id.empty()) {
        return "";
    }
    
    // Costruisce l'URL di interrogazione
    // Assicurati che l'URL API non termini con '/'
    std::string result = api_url;
    if (!result.empty() && result.back() == '/') {
        result.pop_back();
    }
    
    // Aggiunge '/' e l'ID utente tagliato
    result += '/';
    result += trimmed_user_id;
    
    return result;
}