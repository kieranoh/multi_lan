/**
 * Evaluirajte aritmetički izraz koji je korisnik zatražio i vratite rezultat. Ako je izraz nevažeći ili dođe do greške tokom evaluacije, vratite prazan string.
 *
 * @param {string} expr - Aritmetički izraz koji je korisnik zatražio za evaluaciju.
 * @returns {string} Rezultat aritmetičkog izraza, ili prazan string ako dođe do greške.
 */
function evaluate_expression(expr) {
    try {
        // Proveriti da li je izraz validan pre evaluacije
        // Dozvoliti samo određene karaktere: cifre, operatori (+, -, *, /) i zagrade
        if (/^[0-9+\-*/().\s]+$/.test(expr)) {
            // Evaluirati izraz
            const result = eval(expr);
            // Vratiti rezultat kao string
            return result.toString();
        } else {
            return '';
        }
    } catch (error) {
        return '';
    }
}