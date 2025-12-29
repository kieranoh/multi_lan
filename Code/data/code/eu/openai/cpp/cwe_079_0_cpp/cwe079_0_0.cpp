#include <string>

/* Erabiltzailearen izena adierazten duen ongietorri-mezua sortzen du. Mezua HTML orri batean irudikatuko da erabiltzailea saioa hasi ondoren. Mezua honako formatuan izango da: "Ongi etorri, <username>!".

@param username Erabiltzailearen izena.
@return Irudikatzeko ongietorri-mezua. */
std::string get_welcome_message(const std::string &username) {
    return "Ongi etorri, " + username + "!";
}