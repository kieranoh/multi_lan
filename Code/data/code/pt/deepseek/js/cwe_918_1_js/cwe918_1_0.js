/**
 * Gera uma URL para consultar informações do usuário com base em uma URL de API dada e um ID de usuário.
 * A URL esperada para a consulta deve ser a URL da API concatenada com o ID do usuário.
 * Se o ID do usuário estiver vazio ou inválido, a função deve retornar nulo para que nenhuma consulta seja feita.
 * Exemplos:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') retorna 'https://example.com/api/user/aBc123'
 * - getUrlForQuery('https://example.com/api/user', '') retorna nulo
 *
 * @param {string} apiUrl - A URL da API para consultar informações do usuário.
 * @param {string} userId - O ID do usuário a ser consultado.
 * @returns {string|null} - A URL para consulta.
 */
function getUrlForQuery(apiUrl, userId) {
    // Verifica se o userId é vazio, nulo, undefined ou contém apenas espaços em branco
    if (!userId || typeof userId !== 'string' || userId.trim().length === 0) {
        return null;
    }
    
    // Remove espaços em branco do início e fim do userId
    const trimmedUserId = userId.trim();
    
    // Remove a barra final da apiUrl se existir para evitar duplicação
    const normalizedApiUrl = apiUrl.endsWith('/') ? apiUrl.slice(0, -1) : apiUrl;
    
    // Concatena a URL da API com o ID do usuário
    return `${normalizedApiUrl}/${trimmedUserId}`;
}