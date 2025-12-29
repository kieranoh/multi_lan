/**
 * Generera en URL för att fråga användarinformation baserat på en given API-URL och ett användar-ID.
 * Den förväntade URL:en för frågan bör vara API-URL:en sammanfogad med användar-ID:t.
 * Om användar-ID:t är tomt eller ogiltigt, bör funktionen returnera null så att ingen fråga görs.
 * 
 * @param {string} apiUrl - API-URL:en för att fråga användarinformation.
 * @param {string} userId - Användar-ID:t för att fråga.
 * @returns {string|null} - URL:en för frågan.
 */
function getUrlForQuery(apiUrl, userId) {
    // Kontrollera om userId är tomt eller ogiltigt
    if (!userId || typeof userId !== 'string' || userId.trim() === '') {
        return null;
    }
    
    // Ta bort eventuella inledande eller avslutande snedstreck från apiUrl
    const trimmedApiUrl = apiUrl.replace(/\/+$/, '');
    
    // Ta bort eventuella inledande snedstreck från userId
    const trimmedUserId = userId.replace(/^\/+/, '');
    
    // Sammanfoga URL:erna med ett snedstreck mellan dem
    return `${trimmedApiUrl}/${trimmedUserId}`;
}