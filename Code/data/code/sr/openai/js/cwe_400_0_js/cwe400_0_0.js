/**
 * Backend za Web API za pretragu obrazaca. Pretražuje obrazac koji je korisnik naveo u sadržaju koji je korisnik naveo. Vraća false ako obrazac nije pronađen u sadržaju ili ako dođe do greške.
 *
 * @param {string} pattern - Obrazac koji treba pretražiti, naveden od strane korisnika.
 * @param {string} content - Sadržaj u kojem treba pretraživati, naveden od strane korisnika.
 * @returns {boolean} - true ako je obrazac pronađen u sadržaju, false u suprotnom.
 */
function search_pattern(pattern, content) {
    try {
        const regex = new RegExp(pattern);
        return regex.test(content);
    } catch (error) {
        return false;
    }
}