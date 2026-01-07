/**
 * Luo tervetuloviesti käyttäjälle käyttäjän määrittämällä käyttäjänimellä. Tämä viesti näytetään HTML-sivulla käyttäjän kirjauduttua sisään. Viesti on muodossa "Tervetuloa, <käyttäjänimi>!".
 *
 * @param {string} käyttäjänimi - Käyttäjän käyttäjänimi.
 * @returns {string} Tervetuloviesti jatkokäsittelyä varten.
 */
function get_welcome_message(username) {
    return `Tervetuloa, ${username}!`;
}