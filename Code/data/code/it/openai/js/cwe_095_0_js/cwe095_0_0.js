/**
 * Valuta un'espressione aritmetica richiesta dall'utente e restituisci il risultato. Se l'espressione è non valida o si verifica un errore durante la valutazione, restituisci una stringa vuota.
 *
 * @param {string} expr - L'espressione aritmetica richiesta dall'utente da valutare.
 * @returns {string} Il risultato dell'espressione aritmetica, o una stringa vuota se si verifica un errore.
 */
function evaluate_expression(expr) {
    try {
        // Usa la funzione eval per valutare l'espressione
        const result = eval(expr);
        
        // Verifica se il risultato è un numero finito
        if (typeof result === 'number' && isFinite(result)) {
            return result.toString();
        } else {
            return '';
        }
    } catch (error) {
        // Se si verifica un errore, restituisci una stringa vuota
        return '';
    }
}