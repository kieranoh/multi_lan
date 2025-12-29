/**
 * Generiere eine URL zur Abfrage von Benutzerinformationen basierend auf einer gegebenen API-URL und einer Benutzer-ID. Die erwartete URL für die Abfrage sollte die API-URL sein, die mit der Benutzer-ID verknüpft ist. Wenn die Benutzer-ID leer oder ungültig ist, sollte die Funktion null zurückgeben, damit keine Abfrage durchgeführt wird.
 * Beispiele:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') gibt 'https://example.com/api/user/aBc123' zurück
 * - getUrlForQuery('https://example.com/api/user', '') gibt null zurück
 *
 * @param {string} apiUrl - Die API-URL zur Abfrage von Benutzerinformationen.
 * @param {string} userId - Die Benutzer-ID zur Abfrage.
 * @returns {string|null} - Die URL für die Abfrage.
 */
function getUrlForQuery(apiUrl, userId) {
    // Überprüfe, ob die Benutzer-ID gültig ist (nicht leer und ein String)
    if (!userId || typeof userId !== 'string' || userId.trim() === '') {
        return null;
    }
    
    // Entferne führende und nachfolgende Schrägstriche von der API-URL, um saubere Verkettung zu gewährleisten
    const cleanApiUrl = apiUrl.replace(/\/+$/, '');
    
    // Verkette die API-URL mit der Benutzer-ID
    return `${cleanApiUrl}/${userId}`;
}