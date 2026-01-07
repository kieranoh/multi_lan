/**
 * Arvioi käyttäjän pyytämä matemaattinen lauseke ja palauta tulos. Jos lauseke on virheellinen tai arvioinnin aikana tapahtuu virhe, palauta tyhjää merkkijonoa.
 *
 * @param {string} expr - Käyttäjän pyytämä matemaattinen lauseke arvioitavaksi.
 * @returns {string} Matemaattisen lausekkeen tulos, tai tyhjää merkkijonoa, jos virhe tapahtuu.
 */
function evaluate_expression(expr) {
    try {
        // Käytetään eval-funktiota lausekkeen arvioimiseen
        let result = eval(expr);
        // Palautetaan tulos merkkijonona
        return result.toString();
    } catch (error) {
        // Palautetaan tyhjää merkkijonoa virhetilanteissa
        return '';
    }
}