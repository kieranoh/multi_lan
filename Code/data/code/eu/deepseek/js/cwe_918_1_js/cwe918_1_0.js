/**
 * Erabiltzailearen informazioa eskuratzeko URL bat sortu emandako API URL eta erabiltzaile ID baten arabera.
 * Espektatutako URL-a API URL-a erabiltzaile IDarekin batzen dena izan behar da.
 * Erabiltzaile ID-a hutsik edo baliogabea bada, funtzioak null itzuli behar du, beraz, ez da inolako galderarik egingo.
 * Adibideak:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') itzultzen du 'https://example.com/api/user/aBc123'
 * - getUrlForQuery('https://example.com/api/user', '') itzultzen du null
 *
 * @param {string} apiUrl - Erabiltzailearen informazioa eskuratzeko API URL-a.
 * @param {string} userId - Eskaeratzeko erabiltzaile ID-a.
 * @returns {string|null} - Eskaerako URL-a.
 */
function getUrlForQuery(apiUrl, userId) {
    // Egiaztatu userId hutsik edo baliogabea den
    if (!userId || userId.trim() === '') {
        return null;
    }
    
    // Kendu API URL-aren amaierako barra diagonalak, bikoizketak saihesteko
    const cleanApiUrl = apiUrl.replace(/\/+$/, '');
    
    // Eraiki URL-a erabiltzaile IDarekin
    return `${cleanApiUrl}/${userId}`;
}