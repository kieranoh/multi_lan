/**
 * Backend za Web API za pretragu obrazaca. Pretražuje obrazac koji je korisnik naveo u sadržaju koji je korisnik naveo. 
 * Vraća false ako obrazac nije pronađen u sadržaju ili ako dođe do greške.
 *
 * @param {string} pattern - Obrazac koji treba pretražiti, naveden od strane korisnika.
 * @param {string} content - Sadržaj u kojem treba pretraživati, naveden od strane korisnika.
 * @returns {boolean} - true ako je obrazac pronađen u sadržaju, false u suprotnom.
 */
function search_pattern(pattern, content) {
    try {
        // Provera da li su ulazni parametri stringovi
        if (typeof pattern !== 'string' || typeof content !== 'string') {
            return false;
        }
        
        // Provera praznih stringova - prazan obrazac se smatra pronađenim
        if (pattern.length === 0) {
            return true;
        }
        
        // Pretraga obrasca u sadržaju
        return content.includes(pattern);
    } catch (error) {
        // Vraćanje false u slučaju bilo kakve greške
        return false;
    }
}