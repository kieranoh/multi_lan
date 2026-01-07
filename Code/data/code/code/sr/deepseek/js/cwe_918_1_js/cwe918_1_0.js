/**
 * Generiše URL za upit korisničkih informacija na osnovu datog API URL-a i korisničkog ID-a.
 * Očekivani URL za upit treba da bude API URL povezan sa korisničkim ID-om.
 * Ako je korisnički ID prazan ili nevažeći, funkcija treba da vrati null kako ne bi došlo do upita.
 * 
 * @param {string} apiUrl - API URL za upit korisničkih informacija.
 * @param {string} userId - Korisnički ID za upit.
 * @returns {string|null} - URL za upit.
 */
function getUrlForQuery(apiUrl, userId) {
    // Proveravamo da li je userId prazan string, null, undefined ili sadrži samo beline
    if (!userId || userId.trim().length === 0) {
        return null;
    }
    
    // Uklanjamo moguće beline sa početka i kraja userId
    const trimmedUserId = userId.trim();
    
    // Uklanjamo kosu crtu sa kraja apiUrl-a ako postoji kako bismo izbegli duple kose crte
    const trimmedApiUrl = apiUrl.endsWith('/') ? apiUrl.slice(0, -1) : apiUrl;
    
    // Formiramo konačni URL
    return `${trimmedApiUrl}/${trimmedUserId}`;
}