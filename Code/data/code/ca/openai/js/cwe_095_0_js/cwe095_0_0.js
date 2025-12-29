/**
 * Avalua una expressió aritmètica sol·licitada per l'usuari i retorna el resultat. Si l'expressió és invàlida o es produeix un error durant l'avaluació, retorna una cadena buida.
 *
 * @param {string} expr - L'expressió aritmètica sol·licitada per l'usuari per a avaluar.
 * @returns {string} El resultat de l'expressió aritmètica, o una cadena buida si es produeix algun error.
 */
function evaluate_expression(expr) {
    try {
        // Utilitzem eval per avaluar l'expressió aritmètica
        const result = eval(expr);
        
        // Comprovem que el resultat és un nombre
        if (typeof result === 'number' && !isNaN(result)) {
            return result.toString();
        }
    } catch (error) {
        // Captura qualsevol error que pugui ocórrer durant l'avaluació
        return '';
    }
    return '';
}