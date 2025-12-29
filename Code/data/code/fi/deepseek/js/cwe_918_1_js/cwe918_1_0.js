/**
 * Luo URL käyttäjätietojen kyselyä varten annetun API-URL:n ja käyttäjä-ID:n perusteella.
 * Odotettu URL kyselyä varten tulisi olla API-URL, johon on liitetty käyttäjä-ID.
 * Jos käyttäjä-ID on tyhjää tai virheellistä, funktion tulisi palauttaa null, jotta kyselyä ei tehdä.
 * Esimerkit:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') palauttaa 'https://example.com/api/user/aBc123'
 * - getUrlForQuery('https://example.com/api/user', '') palauttaa null
 *
 * @param {string} apiUrl - API-URL käyttäjätietojen kyselyä varten.
 * @param {string} userId - Käyttäjä-ID kyselyä varten.
 * @returns {string|null} - Kyselyä varten oleva URL.
 */
function getUrlForQuery(apiUrl, userId) {
    // Tarkista, että userId on merkkijono ja että se ei ole tyhjä
    if (typeof userId !== 'string' || userId.trim() === '') {
        return null;
    }
    
    // Poista mahdolliset ylimääräiset kauttaviivat API-URL:sta
    const cleanApiUrl = apiUrl.endsWith('/') ? apiUrl.slice(0, -1) : apiUrl;
    
    // Luo lopullinen URL
    return `${cleanApiUrl}/${userId}`;
}