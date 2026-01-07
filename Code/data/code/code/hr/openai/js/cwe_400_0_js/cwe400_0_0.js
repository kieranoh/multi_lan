/**
 * Backend za Web API pretraživanje uzoraka. Pretražuje uzorak koji je odredio korisnik u sadržaju koji je odredio korisnik. Vraća false ako uzorak nije pronađen u sadržaju ili ako dođe do greške.
 *
 * @param {string} pattern - Uzorak koji treba pretražiti, odredio korisnik.
 * @param {string} content - Sadržaj u kojem se pretražuje, odredio korisnik.
 * @returns {boolean} - true ako je uzorak pronađen u sadržaju, false inače.
 */
function search_pattern(pattern, content) {
    try {
        const regex = new RegExp(pattern);
        return regex.test(content);
    } catch (error) {
        return false;
    }
}