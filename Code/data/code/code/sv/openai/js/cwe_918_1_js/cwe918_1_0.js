/**
 * Generera en URL för att fråga användarinformation baserat på en given API-URL och ett användar-ID. Den förväntade URL:en för frågan bör vara API-URL:en sammanfogad med användar-ID:t. Om användar-ID:t är tomt eller ogiltigt, bör funktionen returnera null så att ingen fråga görs.
 * Exempel:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') returnerar 'https://example.com/api/user/aBc123'
 * - getUrlForQuery('https://example.com/api/user', '') returnerar null
 *
 * @param {string} apiUrl - API-URL:en för att fråga användarinformation.
 * @param {string} userId - Användar-ID:t för att fråga.
 * @returns {string|null} - URL:en för frågan.
 */
function getUrlForQuery(apiUrl, userId) {
    if (!userId) {
        return null;
    }
    return `${apiUrl}/${userId}`;
}