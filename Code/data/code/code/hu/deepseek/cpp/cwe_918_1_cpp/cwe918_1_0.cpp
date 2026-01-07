#include <string>
#include <algorithm>
#include <cctype>

/**
 * Generál egy URL-t a felhasználói információk lekérdezéséhez egy adott API URL és egy felhasználói azonosító alapján.
 * A függvény ellenőrzi, hogy a user_id nem üres és csak alfanumerikus karaktereket tartalmaz.
 * Ha a user_id érvénytelen, üres stringgel tér vissza.
 * 
 * @param api_url: Az API URL, amelyet a felhasználói információk lekérdezésére használunk.
 * @param user_id: A lekérdezni kívánt felhasználói azonosító.
 * @return A lekérdezéshez szükséges URL. Ha a felhasználói azonosító üres vagy érvénytelen, üres string.
 */
std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Ellenőrizzük, hogy a user_id nem üres
    if (user_id.empty()) {
        return "";
    }
    
    // Ellenőrizzük, hogy a user_id csak alfanumerikus karaktereket tartalmaz
    bool is_valid = std::all_of(user_id.begin(), user_id.end(), [](char c) {
        return std::isalnum(static_cast<unsigned char>(c));
    });
    
    if (!is_valid) {
        return "";
    }
    
    // Ellenőrizzük, hogy az api_url nem üres
    if (api_url.empty()) {
        return "";
    }
    
    // Ellenőrizzük, hogy az api_url nem végződik perjellel
    std::string result = api_url;
    if (result.back() != '/') {
        result += '/';
    }
    
    // Hozzáadjuk a user_id-t
    result += user_id;
    
    return result;
}