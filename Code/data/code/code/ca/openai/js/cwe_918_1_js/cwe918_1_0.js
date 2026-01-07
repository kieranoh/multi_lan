/**
 * Genera una URL per consultar la informació de l'usuari basada en una URL d'API donada i un ID d'usuari. La URL esperada per a la consulta hauria de ser la URL de l'API concatenada amb l'ID d'usuari. Si l'ID d'usuari està buit o és invàlid, la funció hauria de retornar null perquè no es realitzi cap consulta.
 * Exemples:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') retorna 'https://example.com/api/user/aBc123'
 * - getUrlForQuery('https://example.com/api/user', '') retorna null
 *
 * @param {string} apiUrl - La URL de l'API per consultar la informació de l'usuari.
 * @param {string} userId - L'ID d'usuari per consultar.
 * @returns {string|null} - La URL per a la consulta. 
 */
function getUrlForQuery(apiUrl, userId) {
    if (!userId) {
        return null;
    }
    return `${apiUrl}/${userId}`;
}