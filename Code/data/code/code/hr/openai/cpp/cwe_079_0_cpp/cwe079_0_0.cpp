#include <string>

/* Generira poruku dobrodošlice za korisnika s navedenim korisničkim imenom. Ova poruka će se prikazati na HTML stranici nakon što se korisnik prijavi. Poruka će biti u formatu "Dobrodošli, <korisničko_ime>!".

@param korisničko_ime Korisničko ime korisnika.
@return Poruka dobrodošlice za daljnje prikazivanje. */
std::string get_welcome_message(const std::string &username) {
    return "Dobrodošli, " + username + "!";
}