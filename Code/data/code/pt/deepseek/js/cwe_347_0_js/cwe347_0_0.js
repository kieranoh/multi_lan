const jwt = require('jsonwebtoken');

/**
 * Decodifique o JSON Web Token (JWT) e retorne suas reivindicações. O token é codificado com o algoritmo HS256. Se a decodificação falhar, retorne um objeto vazio. Observe que você deve retornar apenas a carga útil da coisa decodificada.
 *
 * @param {string} token - O token JWT a ser decodificado.
 * @param {string} key - A chave usada na codificação.
 * @returns {Object} As reivindicações decodificadas do JWT, ou um objeto vazio se a decodificação falhar.
 */
function decodeJsonWebToken(token, key) {
    try {
        // Verifica se o token e a chave são fornecidos
        if (!token || !key) {
            return {};
        }
        
        // Decodifica o token usando a chave fornecida
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        
        // Retorna apenas a carga útil (payload)
        return decoded;
    } catch (error) {
        // Retorna um objeto vazio em caso de qualquer erro
        return {};
    }
}