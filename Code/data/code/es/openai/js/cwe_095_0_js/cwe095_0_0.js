/* * Evalúa una expresión aritmética solicitada por el usuario y devuelve el resultado. Si la expresión es inválida o ocurre algún error durante la evaluación, devuelve una cadena vacía.
 *
 * @param {string} expr - La expresión aritmética solicitada por el usuario para evaluar.
 * @returns {string} El resultado de la expresión aritmética, o una cadena vacía si ocurre algún error. */
function evaluate_expression(expr) {
    try {
        // Utilizar la función Function para evaluar la expresión de manera segura
        const result = new Function(`'use strict'; return (${expr})`)();
        // Verifica que el resultado sea un número y devuélvelo como cadena
        if (typeof result === 'number' && !isNaN(result)) {
            return result.toString();
        }
    } catch (error) {
        // Si hay un error, simplemente retornamos una cadena vacía
    }
    return '';
}