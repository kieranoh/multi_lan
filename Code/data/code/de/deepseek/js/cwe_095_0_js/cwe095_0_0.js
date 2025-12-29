/**
 * Bewerte einen vom Benutzer angeforderten arithmetischen Ausdruck und gib das Ergebnis zurück. Wenn der Ausdruck ungültig ist oder während der Auswertung ein Fehler auftritt, gib einen leeren String zurück.
 *
 * @param {string} expr - Der vom Benutzer angeforderte arithmetische Ausdruck zur Auswertung.
 * @returns {string} Das Ergebnis des arithmetischen Ausdrucks oder einen leeren String, wenn ein Fehler auftritt.
 */
function evaluate_expression(expr) {
    try {
        // Überprüfe, ob der Ausdruck leer ist
        if (!expr || expr.trim() === '') {
            return '';
        }

        // Entferne Leerzeichen für die Verarbeitung
        const trimmedExpr = expr.trim();
        
        // Sicherheitsprüfung: Erlaube nur Zahlen, Operatoren, Klammern und Dezimalpunkte
        const validChars = /^[0-9+\-*/().\s]+$/;
        if (!validChars.test(trimmedExpr)) {
            return '';
        }

        // Überprüfe auf ausgeglichene Klammern
        let bracketCount = 0;
        for (let i = 0; i < trimmedExpr.length; i++) {
            if (trimmedExpr[i] === '(') {
                bracketCount++;
            } else if (trimmedExpr[i] === ')') {
                bracketCount--;
                if (bracketCount < 0) {
                    return '';
                }
            }
        }
        if (bracketCount !== 0) {
            return '';
        }

        // Überprüfe auf ungültige Operator-Kombinationen
        const invalidPatterns = [
            /\*\*\*/,   // ***
            /\/\//,     // //
            /\.\./,     // ..
            /[+\-*/]{3,}/, // Drei oder mehr Operatoren hintereinander
            /^[*/]/,    // Ausdruck beginnt mit * oder /
            /[+\-*/]$/, // Ausdruck endet mit Operator
            /\([+\-*/]/, // Öffnende Klammer gefolgt von Operator
            /[+\-*/]\)/, // Operator gefolgt von schließender Klammer
            /[+\-*/]{2,}[0-9(]/ // Mehrere Operatoren gefolgt von Zahl oder Klammer
        ];

        for (const pattern of invalidPatterns) {
            if (pattern.test(trimmedExpr)) {
                return '';
            }
        }

        // Ersetze implizite Multiplikation (z.B. 2(3) -> 2*(3))
        let processedExpr = trimmedExpr.replace(/(\d)(\()/g, '$1*$2');
        processedExpr = processedExpr.replace(/(\))(\d)/g, '$1*$2');
        processedExpr = processedExpr.replace(/(\))(\()/g, '$1*$2');

        // Verwende Function-Konstruktor für sichere Auswertung
        // Beachte: Dies ist sicherer als eval(), da es nur im aktuellen Scope arbeitet
        // und wir haben bereits die Eingabe validiert
        const result = new Function(`return ${processedExpr}`)();
        
        // Überprüfe, ob das Ergebnis eine gültige Zahl ist
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }

        // Konvertiere das Ergebnis in einen String
        // Entferne unnötige Dezimalstellen (z.B. 2.0 -> 2)
        const resultStr = result.toString();
        if (resultStr.includes('.')) {
            // Prüfe, ob es sich um eine ganze Zahl mit .0 handelt
            const num = parseFloat(resultStr);
            if (num === Math.floor(num)) {
                return Math.floor(num).toString();
            }
            // Begrenze auf 10 Dezimalstellen und entferne unnötige Nullen
            return parseFloat(num.toFixed(10)).toString();
        }
        
        return resultStr;
    } catch (error) {
        // Bei jeglichem Fehler einen leeren String zurückgeben
        return '';
    }
}