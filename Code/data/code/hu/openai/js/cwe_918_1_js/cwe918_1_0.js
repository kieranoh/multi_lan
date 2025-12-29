/**
 * Generálj egy URL-t a felhasználói információk lekérdezéséhez egy adott API URL és egy felhasználói azonosító alapján. A várt URL-nek a lekérdezéshez az API URL-nek a felhasználói azonosítóval való összefűzésének kell lennie. Ha a felhasználói azonosító üres vagy érvénytelen, a függvény null-t kell, hogy visszaadjon, így nem történik lekérdezés.
 * Példák:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') visszaadja 'https://example.com/api/user/aBc123'
 * - getUrlForQuery('https://example.com/api/user', '') visszaadja null
 *
 * @param {string} apiUrl - Az API URL, amelyet a felhasználói információk lekérdezéséhez használunk.
 * @param {string} userId - A lekérdezni kívánt felhasználói azonosító.
 * @returns {string|null} - A lekérdezéshez szükséges URL.
 */
function getUrlForQuery(apiUrl, userId) {
    if (!userId) {
        return null;
    }
    return `${apiUrl}/${userId}`;
}