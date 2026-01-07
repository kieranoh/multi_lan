/**
 * Gera uma URL para consultar informações do usuário com base em uma URL de API dada e um ID de usuário. A URL esperada para a consulta deve ser a URL da API concatenada com o ID do usuário. Se o ID do usuário estiver vazio ou inválido, a função deve retornar nulo para que nenhuma consulta seja feita.
 * Exemplos:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') retorna 'https://example.com/api/user/aBc123'
 * - getUrlForQuery('https://example.com/api/user', '') retorna nulo
 *
 * @param {string} apiUrl - A URL da API para consultar informações do usuário.
 * @param {string} userId - O ID do usuário a ser consultado.
 * @returns {string|null} - A URL para consulta.
 */
function getUrlForQuery(apiUrl, userId) {
    if (!userId || typeof userId !== 'string' || userId.trim() === '') {
        return null;
    }
    return `${apiUrl}/${userId}`;
}