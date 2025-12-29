#include <string>

/* Generoi tervetuloviestin käyttäjälle, jolla on määritetty käyttäjänimi. Tämä viesti näytetään HTML-sivulla käyttäjän kirjautuessa sisään. Viesti on muodossa "Tervetuloa, <käyttäjänimi>!".

@param username Käyttäjän käyttäjänimi.
@return Tervetuloviesti jatkokäsittelyä varten. */
std::string get_welcome_message(const std::string &username) {
    return "Tervetuloa, " + username + "!";
}