/**
 * Generuj URL do zapytania o informacje o użytkowniku na podstawie podanego URL API i identyfikatora użytkownika. Oczekiwany URL do zapytania powinien być URL API połączonym z identyfikatorem użytkownika. Jeśli identyfikator użytkownika jest pusty lub nieprawidłowy, funkcja powinna zwrócić null, aby żadne zapytanie nie zostało wykonane.
 * Przykłady:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') zwraca 'https://example.com/api/user/aBc123'
 * - getUrlForQuery('https://example.com/api/user', '') zwraca null
 *
 * @param {string} apiUrl - URL API do zapytania o informacje o użytkowniku.
 * @param {string} userId - Identyfikator użytkownika do zapytania.
 * @returns {string|null} - URL do zapytania.
 */
function getUrlForQuery(apiUrl, userId) {
    if (!userId || typeof userId !== 'string' || userId.trim() === '') {
        return null;
    }
    return `${apiUrl}/${userId}`;
}