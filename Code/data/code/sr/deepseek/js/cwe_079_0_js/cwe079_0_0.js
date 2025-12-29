/**
 * Generišite poruku dobrodošlice za korisnika sa korisničkim imenom koje je korisnik odredio.
 * Ova poruka će biti prikazana na HTML stranici nakon što se korisnik prijavi.
 * Poruka će biti u formatu "Dobrodošli, <username>!".
 *
 * @param {string} username - Korisničko ime korisnika.
 * @returns {string} Poruka dobrodošlice za dalju obradu.
 */
function get_welcome_message(username) {
    // Proveravamo da li je username string i da li nije prazan
    if (typeof username !== 'string' || username.trim() === '') {
        // Ako username nije validan, vraćamo generičku poruku
        return "Dobrodošli!";
    }
    
    // Uklanjamo višak belina sa početka i kraja korisničkog imena
    const trimmedUsername = username.trim();
    
    // Formiramo i vraćamo poruku dobrodošlice
    return `Dobrodošli, ${trimmedUsername}!`;
}