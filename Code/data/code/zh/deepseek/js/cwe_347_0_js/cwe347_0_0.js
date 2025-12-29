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
        // 使用提供的密钥和HS256算法验证并解码令牌
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        // 返回有效负载部分
        return decoded;
    } catch (error) {
        // 如果解码失败，返回空对象
        return {};
    }
}