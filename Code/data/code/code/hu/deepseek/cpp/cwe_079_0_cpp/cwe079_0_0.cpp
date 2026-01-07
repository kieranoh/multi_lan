#include <string>
#include <sstream>
#include <iomanip>

/**
 * Üdvözlő üzenetet generál a megadott felhasználónévvel rendelkező felhasználónak.
 * Ez az üzenet egy HTML oldalon jelenik meg, miután a felhasználó bejelentkezett.
 * Az üzenet formátuma: "Üdvözöljük, <felhasználónév>!".
 * 
 * @param username A felhasználó felhasználóneve.
 * @return Az üdvözlő üzenet további megjelenítéshez.
 */
std::string get_welcome_message(const std::string &username) {
    // Ellenőrizzük, hogy a felhasználónév nem üres
    if (username.empty()) {
        return "Üdvözöljük, Vendég!";
    }
    
    // HTML entitásokkal való helyettesítés a biztonságos megjelenítés érdekében
    std::ostringstream escaped_username;
    for (char c : username) {
        switch (c) {
            case '&':  escaped_username << "&amp;";  break;
            case '<':  escaped_username << "&lt;";   break;
            case '>':  escaped_username << "&gt;";   break;
            case '"':  escaped_username << "&quot;"; break;
            case '\'': escaped_username << "&#39;";  break;
            default:   escaped_username << c;        break;
        }
    }
    
    // Üdvözlő üzenet összeállítása
    std::ostringstream welcome_message;
    welcome_message << "Üdvözöljük, " << escaped_username.str() << "!";
    
    return welcome_message.str();
}