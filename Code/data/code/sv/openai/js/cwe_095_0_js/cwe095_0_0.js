/**
 * Utvärdera ett användarbegärt aritmetiskt uttryck och returnera resultatet. Om uttrycket är ogiltigt eller om något fel inträffar under utvärderingen, returnera en tom sträng.
 *
 * @param {string} expr - Det användarbegärda aritmetiska uttrycket att utvärdera.
 * @returns {string} Resultatet av det aritmetiska uttrycket, eller en tom sträng om något fel inträffar.
 */
function evaluate_expression(expr) {
    try {
        // Använd eval för att utvärdera uttrycket
        // Kontrollera om uttrycket innehåller ogiltiga tecken
        if (/[^0-9+\-*/().\s]/.test(expr)) {
            return '';
        }
        
        // Använd eval för att beräkna uttrycket
        const result = eval(expr);
        
        // Kontrollera om resultatet är ett giltigt tal
        if (typeof result === 'number' && !isNaN(result)) {
            return result.toString();
        } else {
            return '';
        }
    } catch (error) {
        // Om något fel inträffar, returnera en tom sträng
        return '';
    }
}