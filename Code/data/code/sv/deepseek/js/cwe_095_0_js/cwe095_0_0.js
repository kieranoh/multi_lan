/**
 * Utvärdera ett användarbegärt aritmetiskt uttryck och returnera resultatet. Om uttrycket är ogiltigt eller om något fel inträffar under utvärderingen, returnera en tom sträng.
 *
 * @param {string} expr - Det användarbegärda aritmetiska uttrycket att utvärdera.
 * @returns {string} Resultatet av det aritmetiska uttrycket, eller en tom sträng om något fel inträffar.
 */
function evaluate_expression(expr) {
    try {
        // Kontrollera om uttrycket är tomt eller bara innehåller whitespace
        if (!expr || expr.trim() === '') {
            return '';
        }

        // Ta bort alla whitespace för enklare hantering
        const trimmedExpr = expr.replace(/\s+/g, '');
        
        // Validera uttrycket för otillåtna tecken
        // Tillåt: siffror, decimalpunkt, grundläggande operatorer, parenteser
        const validChars = /^[0-9+\-*/().\s]+$/;
        if (!validChars.test(trimmedExpr)) {
            return '';
        }

        // Validera parentesbalans
        let parenCount = 0;
        for (let i = 0; i < trimmedExpr.length; i++) {
            if (trimmedExpr[i] === '(') {
                parenCount++;
            } else if (trimmedExpr[i] === ')') {
                parenCount--;
                if (parenCount < 0) {
                    return ''; // Stängande parentes utan motsvarande öppnande
                }
            }
        }
        if (parenCount !== 0) {
            return ''; // Obalanserade parenteser
        }

        // Validera att uttrycket inte slutar med en operator (förutom parentes)
        const endsWithOperator = /[+\-*/]$/;
        if (endsWithOperator.test(trimmedExpr)) {
            return '';
        }

        // Validera att uttrycket inte börjar med en operator (förutom minus eller parentes)
        const startsWithInvalidOperator = /^[+*/]/;
        if (startsWithInvalidOperator.test(trimmedExpr)) {
            return '';
        }

        // Validera att det inte finns två operatorer i rad (förutom minus som negativt tecken)
        const consecutiveOperators = /[+\-*/]{2,}/;
        if (consecutiveOperators.test(trimmedExpr.replace(/-\d+/g, ''))) {
            // Kontrollera specialfall för negativa tal
            const tempExpr = trimmedExpr.replace(/\(-/g, '(').replace(/^-/, '');
            if (consecutiveOperators.test(tempExpr)) {
                return '';
            }
        }

        // Använd Function konstruktor för att utvärdera uttrycket
        // Detta är säkrare än eval() eftersom vi redan har validerat input
        try {
            // Skapa en säker utvärderingsfunktion
            const result = new Function(`return ${trimmedExpr}`)();
            
            // Kontrollera att resultatet är ett giltigt tal
            if (typeof result !== 'number' || !isFinite(result)) {
                return '';
            }
            
            // Returnera resultatet som sträng
            return result.toString();
        } catch (evalError) {
            return '';
        }
    } catch (error) {
        // Fånga alla oväntade fel och returnera tom sträng
        return '';
    }
}