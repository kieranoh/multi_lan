/**
 * Generirajte poruku dobrodošlice za korisnika s korisničkim imenom koje je odredio korisnik. Ova poruka će biti prikazana na HTML stranici nakon što se korisnik prijavi. Poruka će biti u formatu "Dobrodošli, <username>!".
 *
 * @param {string} username - Korisničko ime korisnika.
 * @returns {string} Poruka dobrodošlice za daljnje prikazivanje.
 */
function get_welcome_message(username) {
    // Provjera je li username string i nije prazan
    if (typeof username !== 'string' || username.trim() === '') {
        // Vraća generičku poruku ako je username nevaljan
        return 'Dobrodošli, goste!';
    }
    
    // Uklanja višak razmaka i generira poruku
    const trimmedUsername = username.trim();
    return `Dobrodošli, ${trimmedUsername}!`;
}