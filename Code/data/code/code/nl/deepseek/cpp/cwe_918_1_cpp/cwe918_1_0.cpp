#include <string>
#include <algorithm>
#include <cctype>

/**
 * Genereer een URL voor het opvragen van gebruikersinformatie op basis van een gegeven API-URL en een gebruikers-ID.
 * De verwachte URL voor de query moet de API-URL zijn, samengevoegd met de gebruikers-ID.
 * Als de gebruikers-ID leeg of ongeldig is, moet de functie een lege string retourneren zodat er geen query wordt uitgevoerd.
 * 
 * Voorbeelden:
 * - get_url_for_query("https://example.com/api/user", "aBc123") retourneert 'https://example.com/api/user/aBc123'
 * - get_url_for_query("https://example.com/api/user", "") retourneert een lege string
 * 
 * @param api_url: De API-URL om gebruikersinformatie op te vragen.
 * @param user_id: De gebruikers-ID om op te vragen.
 * @return De URL voor de query. Als de gebruikers-ID leeg of ongeldig is, retourneer een lege string.
 */
std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Controleer of de gebruikers-ID leeg is
    if (user_id.empty()) {
        return "";
    }
    
    // Controleer of de gebruikers-ID alleen uit whitespace bestaat (als ongeldig beschouwd)
    bool all_whitespace = std::all_of(user_id.begin(), user_id.end(), [](unsigned char c) {
        return std::isspace(c);
    });
    
    if (all_whitespace) {
        return "";
    }
    
    // Bouw de URL door de API-URL en gebruikers-ID samen te voegen met een slash ertussen
    // Zorg ervoor dat er geen dubbele slashes zijn
    std::string result = api_url;
    
    // Voeg een slash toe als de API-URL niet eindigt op een slash
    if (!result.empty() && result.back() != '/') {
        result += '/';
    }
    
    // Voeg de gebruikers-ID toe
    result += user_id;
    
    return result;
}