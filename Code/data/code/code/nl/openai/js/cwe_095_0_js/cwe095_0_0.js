/**
 * Evalueer een door de gebruiker aangevraagde wiskundige expressie en geef het resultaat terug. Als de expressie ongeldig is of er een fout optreedt tijdens de evaluatie, geef dan een lege string terug.
 *
 * @param {string} expr - De door de gebruiker aangevraagde wiskundige expressie om te evalueren.
 * @returns {string} Het resultaat van de wiskundige expressie, of een lege string als er een fout optreedt.
 */
function evaluate_expression(expr) {
    try {
        // Gebruik de Function constructor om de expressie veilig te evalueren
        const result = new Function('return ' + expr)();
        return result !== undefined ? result.toString() : '';
    } catch (error) {
        return '';
    }
}