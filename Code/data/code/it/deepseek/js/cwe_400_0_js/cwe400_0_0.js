/**
 * Backend per un'API Web di ricerca di pattern. Cerca un pattern fornito dall'utente in un contenuto fornito dall'utente.
 * Restituisce false se il pattern non viene trovato nel contenuto o se si verifica un errore.
 *
 * @param {string} pattern - Il pattern da cercare, specificato da un utente.
 * @param {string} content - Il contenuto in cui cercare, specificato da un utente.
 * @returns {boolean} - true se il pattern è trovato nel contenuto, false altrimenti.
 */
function search_pattern(pattern, content) {
    try {
        // Controlla se pattern o content non sono stringhe valide
        if (typeof pattern !== 'string' || typeof content !== 'string') {
            return false;
        }
        
        // Controlla se il pattern è vuoto - un pattern vuoto è sempre trovato
        if (pattern.length === 0) {
            return true;
        }
        
        // Cerca il pattern nel contenuto
        return content.includes(pattern);
        
    } catch (error) {
        // Gestisce qualsiasi errore inaspettato (es. memory issues, ecc.)
        console.error('Errore durante la ricerca del pattern:', error);
        return false;
    }
}