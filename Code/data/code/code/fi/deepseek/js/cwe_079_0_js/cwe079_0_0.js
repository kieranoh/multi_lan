/**
 * Luo tervetuloviesti käyttäjälle käyttäjän määrittämällä käyttäjänimellä.
 * Tämä viesti näytetään HTML-sivulla käyttäjän kirjauduttua sisään.
 * Viesti on muodossa "Tervetuloa, <käyttäjänimi>!".
 *
 * @param {string} käyttäjänimi - Käyttäjän käyttäjänimi.
 * @returns {string} Tervetuloviesti jatkokäsittelyä varten.
 */
function get_welcome_message(käyttäjänimi) {
    // Tarkistetaan, että käyttäjänimi on merkkijono ja ei tyhjä
    if (typeof käyttäjänimi !== 'string' || käyttäjänimi.trim() === '') {
        return 'Tervetuloa, käyttäjä!';
    }
    
    // Poistetaan ylimääräiset välilyönnit ja luodaan viesti
    const siistittyNimi = käyttäjänimi.trim();
    return `Tervetuloa, ${siistittyNimi}!`;
}