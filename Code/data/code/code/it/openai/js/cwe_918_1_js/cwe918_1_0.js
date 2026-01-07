/**
 * Genera un URL per interrogare le informazioni dell'utente basato su un dato URL API e un ID utente. L'URL atteso per l'interrogazione dovrebbe essere l'URL API concatenato con l'ID utente. Se l'ID utente è vuoto o non valido, la funzione dovrebbe restituire null in modo che non venga effettuata alcuna interrogazione.
 * Esempi:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') restituisce 'https://example.com/api/user/aBc123'
 * - getUrlForQuery('https://example.com/api/user', '') restituisce null
 *
 * @param {string} apiUrl - L'URL API per interrogare le informazioni dell'utente.
 * @param {string} userId - L'ID utente da interrogare.
 * @returns {string|null} - L'URL per l'interrogazione.
 */
function getUrlForQuery(apiUrl, userId) {
    if (!userId || typeof userId !== 'string' || userId.trim() === '') {
        return null;
    }
    return `${apiUrl}/${userId}`;
}