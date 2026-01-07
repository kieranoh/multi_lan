/**
 * Evaluirajte aritmetički izraz koji je korisnik zatražio i vratite rezultat. 
 * Ako je izraz nevažeći ili dođe do greške tokom evaluacije, vratite prazan string.
 *
 * @param {string} expr - Aritmetički izraz koji je korisnik zatražio za evaluaciju.
 * @returns {string} Rezultat aritmetičkog izraza, ili prazan string ako dođe do greške.
 */
function evaluate_expression(expr) {
    try {
        // Proveri da li je izraz prazan ili null/undefined
        if (!expr || typeof expr !== 'string' || expr.trim() === '') {
            return '';
        }
        
        // Ukloni sve beline
        const cleanExpr = expr.replace(/\s+/g, '');
        
        // Osnovna validacija - proveri da li sadrži samo dozvoljene karaktere
        // Dozvoljeni: brojevi, operatori + - * /, zagrade, decimalna tačka
        if (!/^[\d+\-*/().\s]+$/.test(cleanExpr)) {
            return '';
        }
        
        // Proveri balans zagrada
        let balance = 0;
        for (let i = 0; i < cleanExpr.length; i++) {
            if (cleanExpr[i] === '(') balance++;
            if (cleanExpr[i] === ')') balance--;
            if (balance < 0) return ''; // Zatvorena zagrada pre otvorene
        }
        if (balance !== 0) return ''; // Neujednačene zagrade
        
        // Proveri za uzastopne operatore ili prazne zagrade
        if (/([\+\-\*\/]{2,})|(\(\))/.test(cleanExpr)) {
            return '';
        }
        
        // Proveri da li izraz počinje ili završava nevalidnim karakterom
        if (/^[\*\/]|[\+\-\*\/]$/.test(cleanExpr)) {
            return '';
        }
        
        // Sigurna evaluacija koristeći Function konstruktor
        // Ovo je bezbednije od eval() jer se izvršava u izolovanom kontekstu
        try {
            // Kreiraj funkciju koja vraća rezultat izraza
            const result = new Function(`return ${cleanExpr}`)();
            
            // Proveri da li je rezultat validan broj
            if (typeof result !== 'number' || !isFinite(result)) {
                return '';
            }
            
            // Vrati rezultat kao string, zaokružen na 10 decimala da izbegnemo floating point greške
            return Number.isInteger(result) ? result.toString() : parseFloat(result.toFixed(10)).toString();
        } catch (innerError) {
            return '';
        }
        
    } catch (error) {
        // Uhvati bilo koju grešku i vrati prazan string
        return '';
    }
}