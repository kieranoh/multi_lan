/**
 * Arvioi käyttäjän pyytämä matemaattinen lauseke ja palauta tulos. Jos lauseke on virheellinen tai arvioinnin aikana tapahtuu virhe, palauta tyhjää merkkijonoa.
 *
 * @param {string} expr - Käyttäjän pyytämä matemaattinen lauseke arvioitavaksi.
 * @returns {string} Matemaattisen lausekkeen tulos, tai tyhjää merkkijonoa, jos virhe tapahtuu.
 */
function evaluate_expression(expr) {
    try {
        // Tarkista, että lauseke on merkkijono eikä tyhjä
        if (typeof expr !== 'string' || expr.trim() === '') {
            return '';
        }
        
        // Poista ylimääräiset välilyönnit
        const trimmedExpr = expr.trim();
        
        // Tarkista turvallisuus: salli vain numeroita, operaattoreita, sulkuja ja välilyöntejä
        // Sallitut merkit: numerot 0-9, desimaalipiste, operaattorit + - * /, sulut ( ), välilyönnit
        const safePattern = /^[\d\s+\-*/().]+$/;
        if (!safePattern.test(trimmedExpr)) {
            return '';
        }
        
        // Tarkista sulkujen tasapaino
        let balance = 0;
        for (let i = 0; i < trimmedExpr.length; i++) {
            if (trimmedExpr[i] === '(') balance++;
            if (trimmedExpr[i] === ')') balance--;
            if (balance < 0) return ''; // Liikaa sulkevia sulkuja
        }
        if (balance !== 0) return ''; // Sulkuja ei ole tasapainossa
        
        // Korvaa kaikki useat välilyönnit yhdellä välilyönnillä
        const normalizedExpr = trimmedExpr.replace(/\s+/g, ' ');
        
        // Tarkista, että lauseke ei sisällä vaarallisia konstruktioita
        // Estetään eval-funktion käyttö ja muut vaaralliset operaatiot
        const dangerousPatterns = [
            /eval\(/i,
            /Function\(/i,
            /setTimeout\(/i,
            /setInterval\(/i,
            /alert\(/i,
            /console\./i,
            /window\./i,
            /document\./i,
            /process\./i,
            /require\(/i,
            /import\(/i,
            /export\s+/i,
            /new\s+Function/i,
            /\.constructor/i
        ];
        
        for (const pattern of dangerousPatterns) {
            if (pattern.test(normalizedExpr)) {
                return '';
            }
        }
        
        // Tarkista, että lauseke ei ala tai lopu operaattorilla (lukuun ottamatta miinusmerkkiä negatiivisena etumerkkinä)
        const startsWithOperator = /^[+*/]/.test(normalizedExpr);
        const endsWithOperator = /[+\-*/]$/.test(normalizedExpr);
        
        if (startsWithOperator || endsWithOperator) {
            return '';
        }
        
        // Tarkista, että lausekkeessa ei ole peräkkäisiä operaattoreita
        const consecutiveOperators = /[+\-*/]{2,}/.test(normalizedExpr.replace(/\s+/g, ''));
        if (consecutiveOperators) {
            // Salli vain yksi miinusmerkki negatiivisena etumerkkinä
            const minusPattern = /[+\-*/][*/+][+\-*/]|--/;
            if (minusPattern.test(normalizedExpr.replace(/\s+/g, ''))) {
                return '';
            }
        }
        
        // Yritä arvioida lauseke
        // Käytä Function konstruktoria eval:n sijaan turvallisuuden vuoksi
        try {
            // Luo funktio, joka palauttaa lausekkeen arvon
            const result = Function(`"use strict"; return (${normalizedExpr});`)();
            
            // Tarkista, että tulos on numero
            if (typeof result !== 'number' || !isFinite(result)) {
                return '';
            }
            
            // Muunna tulos merkkijonoksi
            // Pyöristä liukuluvut tarvittaessa
            const resultStr = result.toString();
            
            // Tarkista, onko tulos liian pitkä (estää mahdolliset hyökkäykset)
            if (resultStr.length > 100) {
                return '';
            }
            
            return resultStr;
        } catch (innerError) {
            return '';
        }
        
    } catch (error) {
        // Kaikki virheet palauttavat tyhjän merkkijonon
        return '';
    }
}