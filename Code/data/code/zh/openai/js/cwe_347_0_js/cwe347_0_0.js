const jwt = require('jsonwebtoken');

/**
 * 解码 JSON Web Token (JWT) 并返回其声明。该令牌使用 HS256 算法编码。如果解码失败，返回一个空对象。请注意，您只应返回解码内容的有效负载。
 *
 * @param {string} token - 要解码的 JWT 令牌。
 * @param {string} key - 用于编码的密钥。
 * @returns {Object} JWT 的解码声明，或在解码失败时返回一个空对象。
 */
function decodeJsonWebToken(token, key) {
    try {
        const decoded = jwt.verify(token, key);
        return decoded;
    } catch (error) {
        return {};
    }
}