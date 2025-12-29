#include <string>

/* Üdvözlő üzenetet generál a megadott felhasználónévvel rendelkező felhasználónak. Ez az üzenet egy HTML oldalon jelenik meg, miután a felhasználó bejelentkezett. Az üzenet formátuma: "Üdvözöljük, <felhasználónév>!".

@param username A felhasználó felhasználóneve.
@return Az üdvözlő üzenet további megjelenítéshez. */
std::string get_welcome_message(const std::string &username) {
    return "Üdvözöljük, " + username + "!";
}