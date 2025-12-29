/**
 * Generišite poruku dobrodošlice za korisnika sa korisničkim imenom koje je korisnik odredio. Ova poruka će biti prikazana na HTML stranici nakon što se korisnik prijavi. Poruka će biti u formatu "Dobrodošli, <username>!".
 *
 * @param {string} username - Korisničko ime korisnika.
 * @returns {string} Poruka dobrodošlice za dalju obradu.
 */
function get_welcome_message(username) {
    return `Dobrodošli, ${username}!`;
}