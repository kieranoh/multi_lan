/**
 * Generišite URL za upit korisničkih informacija na osnovu datog API URL-a i korisničkog ID-a. Očekivani URL za upit treba da bude API URL povezan sa korisničkim ID-om. Ako je korisnički ID prazan ili nevažeći, funkcija treba da vrati null kako ne bi došlo do upita.
 * Primeri:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') vraća 'https://example.com/api/user/aBc123'
 * - getUrlForQuery('https://example.com/api/user', '') vraća null
 *
 * @param {string} apiUrl - API URL za upit korisničkih informacija.
 * @param {string} userId - Korisnički ID za upit.
 * @returns {string|null} - URL za upit.
 */
function getUrlForQuery(apiUrl, userId) {
    if (!userId) {
        return null;
    }
    return `${apiUrl}/${userId}`;
}