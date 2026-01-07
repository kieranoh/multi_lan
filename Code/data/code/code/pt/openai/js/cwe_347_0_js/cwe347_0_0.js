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
        const decoded = jwt.verify(token, key);
        return decoded;
    } catch (error) {
        return {};
    }
}