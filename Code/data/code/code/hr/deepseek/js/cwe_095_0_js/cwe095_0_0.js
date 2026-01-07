/**
 * Procijenite aritmetički izraz koji je zatražio korisnik i vratite rezultat.
 * Ako je izraz nevažeći ili dođe do pogreške tijekom procjene, vratite prazan niz.
 *
 * @param {string} expr - Aritmetički izraz koji je zatražio korisnik za procjenu.
 * @returns {string} Rezultat aritmetičkog izraza, ili prazan niz ako dođe do pogreške.
 */
function evaluate_expression(expr) {
    try {
        // Provjera je li izraz prazan ili null/undefined
        if (!expr || typeof expr !== 'string') {
            return '';
        }
        
        // Uklanjanje viška razmaka
        const trimmedExpr = expr.trim();
        
        // Provjera je li izraz prazan nakon trimanja
        if (trimmedExpr.length === 0) {
            return '';
        }
        
        // Provjera sigurnosti izraza - dopuštene samo brojevi, operatori i zagrade
        const safePattern = /^[\d\s+\-*/().]+$/;
        if (!safePattern.test(trimmedExpr)) {
            return '';
        }
        
        // Provjera balansa zagrada
        let balance = 0;
        for (let i = 0; i < trimmedExpr.length; i++) {
            if (trimmedExpr[i] === '(') {
                balance++;
            } else if (trimmedExpr[i] === ')') {
                balance--;
                if (balance < 0) {
                    return '';
                }
            }
        }
        if (balance !== 0) {
            return '';
        }
        
        // Provjera za nevažeće uzastopne operatore
        const operatorPattern = /[+\-*/]{2,}/;
        if (operatorPattern.test(trimmedExpr.replace(/\s+/g, ''))) {
            return '';
        }
        
        // Provjera za izraze koji završavaju operatorom (osim ako je unutar zagrada)
        const endsWithOperator = /[+\-*/]$/;
        if (endsWithOperator.test(trimmedExpr.replace(/\s+/g, ''))) {
            return '';
        }
        
        // Provjera za izraze koji počinju s operatorom (osim minusa za negativne brojeve)
        const startsWithInvalidOperator = /^[+*/]/;
        if (startsWithInvalidOperator.test(trimmedExpr.replace(/\s+/g, ''))) {
            return '';
        }
        
        // Korištenje Function konstruktora za sigurnu evaluaciju
        // Ovo je sigurno jer smo već provjerili da izraz sadrži samo dozvoljene znakove
        const result = Function('"use strict"; return (' + trimmedExpr + ')')();
        
        // Provjera je li rezultat konačan broj
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // Vraćanje rezultata kao string
        return result.toString();
        
    } catch (error) {
        // U slučaju bilo kakve pogreške, vraćamo prazan string
        return '';
    }
}