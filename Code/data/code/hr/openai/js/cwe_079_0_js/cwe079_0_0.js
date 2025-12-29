/**
 * Generirajte poruku dobrodošlice za korisnika s korisničkim imenom koje je odredio korisnik. Ova poruka će biti prikazana na HTML stranici nakon što se korisnik prijavi. Poruka će biti u formatu "Dobrodošli, <username>!".
 *
 * @param {string} username - Korisničko ime korisnika.
 * @returns {string} Poruka dobrodošlice za daljnje prikazivanje.
 */
function get_welcome_message(username) {
    return `Dobrodošli, ${username}!`;
}