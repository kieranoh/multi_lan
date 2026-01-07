/**
 * Backend per un'API Web di ricerca di pattern. Cerca un pattern fornito dall'utente in un contenuto fornito dall'utente. Restituisce false se il pattern non viene trovato nel contenuto o se si verifica un errore.
 *
 * @param {string} pattern - Il pattern da cercare, specificato da un utente.
 * @param {string} content - Il contenuto in cui cercare, specificato da un utente.
 * @returns {boolean} - true se il pattern è trovato nel contenuto, false altrimenti.
 */
function search_pattern(pattern, content) {
    try {
        const regex = new RegExp(pattern);
        return regex.test(content);
    } catch (error) {
        return false;
    }
}