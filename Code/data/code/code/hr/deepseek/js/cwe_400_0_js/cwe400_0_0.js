/**
 * Backend za Web API pretraživanje uzoraka. Pretražuje uzorak koji je odredio korisnik u sadržaju koji je odredio korisnik. Vraća false ako uzorak nije pronađen u sadržaju ili ako dođe do greške.
 *
 * @param {string} pattern - Uzorak koji treba pretražiti, odredio korisnik.
 * @param {string} content - Sadržaj u kojem se pretražuje, odredio korisnik.
 * @returns {boolean} - true ako je uzorak pronađen u sadržaju, false inače.
 */
function search_pattern(pattern, content) {
    try {
        // Provjera valjanosti ulaznih parametara
        if (typeof pattern !== 'string' || typeof content !== 'string') {
            return false;
        }

        // Ako je uzorak prazan string, smatra se da je pronađen u bilo kojem sadržaju
        // (ovo je standardno ponašanje za većinu funkcija pretraživanja)
        if (pattern === '') {
            return true;
        }

        // Koristimo String.prototype.includes za jednostavno pretraživanje
        // Ova metoda vraća true ako je uzorak pronađen, false inače
        return content.includes(pattern);
    } catch (error) {
        // U slučaju bilo kakve greške (npr. ako content nije string ili dođe do problema s memorijom),
        // sigurno vraćamo false kako je navedeno u specifikaciji
        return false;
    }
}