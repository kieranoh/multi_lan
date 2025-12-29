/**
 * Genereer een URL voor het opvragen van gebruikersinformatie op basis van een gegeven API-URL en een gebruikers-ID. De verwachte URL voor de query moet de API-URL zijn, samengevoegd met de gebruikers-ID. Als de gebruikers-ID leeg of ongeldig is, moet de functie null retourneren zodat er geen query wordt uitgevoerd.
 * Voorbeelden:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') retourneert 'https://example.com/api/user/aBc123'
 * - getUrlForQuery('https://example.com/api/user', '') retourneert null
 *
 * @param {string} apiUrl - De API-URL om gebruikersinformatie op te vragen.
 * @param {string} userId - De gebruikers-ID om op te vragen.
 * @returns {string|null} - De URL voor de query.
 */
function getUrlForQuery(apiUrl, userId) {
    if (!userId) {
        return null;
    }
    return `${apiUrl}/${userId}`;
}