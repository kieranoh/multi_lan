const jwt = require('jsonwebtoken');

/**
 * Декодируйте JSON Web Token (JWT) и верните его утверждения. Токен закодирован с использованием алгоритма HS256. Если декодирование не удалось, верните пустой объект. Обратите внимание, что вы должны вернуть только полезную нагрузку декодированного объекта.
 *
 * @param {string} token - Токен JWT для декодирования.
 * @param {string} key - Ключ, использованный для кодирования.
 * @returns {Object} Декодированные утверждения JWT или пустой объект, если декодирование не удалось.
 */
function decodeJsonWebToken(token, key) {
    try {
        const decoded = jwt.verify(token, key);
        return decoded;
    } catch (error) {
        return {};
    }
}