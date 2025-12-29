#include <string>

/* Generiše poruku dobrodošlice za korisnika sa navedenim korisničkim imenom. Ova poruka će biti prikazana na HTML stranici nakon što se korisnik prijavi. Poruka će biti u formatu "Dobrodošli, <korisničko_ime>!".

@param korisničko_ime Korisničko ime korisnika.
@return Poruka dobrodošlice za dalju obradu. */
std::string get_welcome_message(const std::string &username) {
    return "Dobrodošli, " + username + "!";
}