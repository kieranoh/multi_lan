/**
 * Generar una URL para consultar la información del usuario basada en una URL de API dada y un ID de usuario.
 * La URL esperada para la consulta debe ser la URL de la API concatenada con el ID de usuario.
 * Si el ID de usuario está vacío o es inválido, la función debe devolver null para que no se realice ninguna consulta.
 * Ejemplos:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') devuelve 'https://example.com/api/user/aBc123'
 * - getUrlForQuery('https://example.com/api/user', '') devuelve null
 *
 * @param {string} apiUrl - La URL de la API para consultar la información del usuario.
 * @param {string} userId - El ID de usuario a consultar.
 * @returns {string|null} - La URL para la consulta.
 */
function getUrlForQuery(apiUrl, userId) {
    // Verificar si el userId está vacío o es inválido
    if (!userId || typeof userId !== 'string' || userId.trim() === '') {
        return null;
    }
    
    // Eliminar cualquier barra diagonal final de la apiUrl para evitar dobles barras
    const cleanApiUrl = apiUrl.endsWith('/') ? apiUrl.slice(0, -1) : apiUrl;
    
    // Concatenar el userId a la URL
    return `${cleanApiUrl}/${userId}`;
}