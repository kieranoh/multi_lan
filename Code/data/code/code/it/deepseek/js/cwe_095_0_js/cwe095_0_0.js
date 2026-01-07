/**
 * Valuta un'espressione aritmetica richiesta dall'utente e restituisci il risultato.
 * Se l'espressione è non valida o si verifica un errore durante la valutazione, restituisci una stringa vuota.
 *
 * @param {string} expr - L'espressione aritmetica richiesta dall'utente da valutare.
 * @returns {string} Il risultato dell'espressione aritmetica, o una stringa vuota se si verifica un errore.
 */
function evaluate_expression(expr) {
    try {
        // Controllo input base
        if (typeof expr !== 'string' || expr.trim() === '') {
            return '';
        }
        
        // Rimuovi spazi e controlla caratteri validi
        const trimmedExpr = expr.trim();
        
        // Espressione regolare per validare caratteri sicuri
        // Permette numeri, operatori aritmetici, parentesi, punto decimale e spazi
        const validCharsRegex = /^[\d+\-*/().\s]+$/;
        
        // Controlla che l'espressione contenga solo caratteri validi
        if (!validCharsRegex.test(trimmedExpr)) {
            return '';
        }
        
        // Controllo bilanciamento parentesi
        let balance = 0;
        for (let i = 0; i < trimmedExpr.length; i++) {
            if (trimmedExpr[i] === '(') {
                balance++;
            } else if (trimmedExpr[i] === ')') {
                balance--;
                if (balance < 0) {
                    return ''; // Parentesi chiuse senza essere aperte
                }
            }
        }
        if (balance !== 0) {
            return ''; // Parentesi non bilanciate
        }
        
        // Controlla che non ci siano operatori consecutivi (eccetto + e - per i numeri negativi)
        const operatorRegex = /[+\-*/]{2,}/;
        if (operatorRegex.test(trimmedExpr.replace(/\s+/g, ''))) {
            // Controlla se è un numero negativo valido
            const negativeNumberRegex = /(\d|\))\s*-\s*\d/;
            if (!negativeNumberRegex.test(trimmedExpr)) {
                return '';
            }
        }
        
        // Valuta l'espressione usando Function constructor in un ambiente controllato
        // Nota: eval() sarebbe più semplice ma Function constructor è leggermente più sicuro
        // in quanto esegue in un contesto globale isolato
        const result = new Function(`return ${trimmedExpr}`)();
        
        // Controlla che il risultato sia un numero valido
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // Restituisci il risultato come stringa
        return result.toString();
        
    } catch (error) {
        // In caso di qualsiasi errore, restituisci stringa vuota
        return '';
    }
}