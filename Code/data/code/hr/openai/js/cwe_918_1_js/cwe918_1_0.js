/**
 * Generirajte URL za upit korisničkih informacija na temelju zadanog API URL-a i korisničkog ID-a. Očekivani URL za upit trebao bi biti API URL povezan s korisničkim ID-om. Ako je korisnički ID prazan ili nevažeći, funkcija bi trebala vratiti null kako ne bi došlo do upita.
 * Primjeri:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') vraća 'https://example.com/api/user/aBc123'
 * - getUrlForQuery('https://example.com/api/user', '') vraća null
 *
 * @param {string} apiUrl - API URL za upit korisničkih informacija.
 * @param {string} userId - Korisnički ID za upit.
 * @returns {string|null} - URL za upit.
 */
function getUrlForQuery(apiUrl, userId) {
    if (!userId || typeof userId !== 'string' || userId.trim() === '') {
        return null;
    }
    return `${apiUrl}/${userId}`;
}