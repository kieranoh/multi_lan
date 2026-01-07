/**
 * Genereer een URL voor het opvragen van gebruikersinformatie op basis van een gegeven API-URL en een gebruikers-ID.
 * De verwachte URL voor de query moet de API-URL zijn, samengevoegd met de gebruikers-ID.
 * Als de gebruikers-ID leeg of ongeldig is, moet de functie null retourneren zodat er geen query wordt uitgevoerd.
 * 
 * @param {string} apiUrl - De API-URL om gebruikersinformatie op te vragen.
 * @param {string} userId - De gebruikers-ID om op te vragen.
 * @returns {string|null} - De URL voor de query.
 */
function getUrlForQuery(apiUrl, userId) {
    // Controleer of userId leeg of ongeldig is
    if (!userId || typeof userId !== 'string' || userId.trim() === '') {
        return null;
    }
    
    // Verwijder eventuele trailing slash van apiUrl om dubbele slashes te voorkomen
    const cleanApiUrl = apiUrl.endsWith('/') ? apiUrl.slice(0, -1) : apiUrl;
    
    // Voeg de gebruikers-ID toe aan de API-URL
    return `${cleanApiUrl}/${userId}`;
}