/**
 * Bewerte einen vom Benutzer angeforderten arithmetischen Ausdruck und gib das Ergebnis zurück. Wenn der Ausdruck ungültig ist oder während der Auswertung ein Fehler auftritt, gib einen leeren String zurück.
 *
 * @param {string} expr - Der vom Benutzer angeforderte arithmetische Ausdruck zur Auswertung.
 * @returns {string} Das Ergebnis des arithmetischen Ausdrucks oder einen leeren String, wenn ein Fehler auftritt.
 */
function evaluate_expression(expr) {
    try {
        // Überprüfen, ob der Ausdruck nur erlaubte Zeichen enthält
        if (/^[0-9+\-*/().\s]*$/.test(expr)) {
            // Auswertung des Ausdrucks und Umwandlung in String
            const result = Function('"use strict";return (' + expr + ')')();
            return String(result);
        } else {
            return '';
        }
    } catch (e) {
        return '';
    }
}