/**
 * Értékelje ki a felhasználó által kért aritmetikai kifejezést, és adja vissza az eredményt. Ha a kifejezés érvénytelen, vagy bármilyen hiba lép fel az értékelés során, adjon vissza egy üres karakterláncot.
 *
 * @param {string} expr - A felhasználó által kért aritmetikai kifejezés, amelyet értékelni kell.
 * @returns {string} Az aritmetikai kifejezés eredménye, vagy egy üres karakterlánc, ha bármilyen hiba lép fel. */
function evaluate_expression(expr) {
    try {
        // Ellenőrizzük, hogy a bemenet egy string-e
        if (typeof expr !== 'string') {
            return '';
        }
        
        // Üres string esetén üres stringet adunk vissza
        if (expr.trim() === '') {
            return '';
        }
        
        // Biztonsági ellenőrzés: csak számok, operátorok, zárójelek, tizedespont és szóközök megengedettek
        const validChars = /^[\d+\-*/().\s]+$/;
        if (!validChars.test(expr)) {
            return '';
        }
        
        // Ellenőrizzük a zárójelek egyensúlyát
        let balance = 0;
        for (let i = 0; i < expr.length; i++) {
            if (expr[i] === '(') {
                balance++;
            } else if (expr[i] === ')') {
                balance--;
                if (balance < 0) {
                    return '';
                }
            }
        }
        if (balance !== 0) {
            return '';
        }
        
        // Ellenőrizzük az operátorok helyességét
        const operatorPattern = /[+\-*/]{2,}/; // Két vagy több egymás melletti operátor
        if (operatorPattern.test(expr.replace(/\s+/g, ''))) {
            return '';
        }
        
        // Kivételkezelés az értékeléshez
        const result = eval(expr);
        
        // Ellenőrizzük, hogy a szám-e az eredmény
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // Visszaadjuk az eredményt stringként
        return String(result);
    } catch (error) {
        // Bármilyen hiba esetén üres stringet adunk vissza
        return '';
    }
}