/**
 * Procijenite aritmetički izraz koji je zatražio korisnik i vratite rezultat. Ako je izraz nevažeći ili dođe do pogreške tijekom procjene, vratite prazan niz.
 *
 * @param {string} expr - Aritmetički izraz koji je zatražio korisnik za procjenu.
 * @returns {string} Rezultat aritmetičkog izraza, ili prazan niz ako dođe do pogreške.
 */
function evaluate_expression(expr) {
    try {
        // Evaluiramo izraz koristeći funkciju 'eval'
        const result = eval(expr);
        
        // Provjeravamo je li rezultat broj
        if (typeof result === 'number') {
            return result.toString(); // Vraćamo rezultat kao string
        } else {
            return ''; // Ako rezultat nije broj, vraćamo prazan niz
        }
    } catch (error) {
        // U slučaju pogreške, vraćamo prazan niz
        return '';
    }
}