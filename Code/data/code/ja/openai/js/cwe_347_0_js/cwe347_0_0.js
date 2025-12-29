const jwt = require('jsonwebtoken');

/* * JSON Web Token (JWT) をデコードし、そのクレームを返します。トークンは HS256 アルゴリズムでエンコードされています。デコードに失敗した場合は、空のオブジェクトを返します。デコードされたもののペイロードのみを返すことに注意してください。
 *
 * @param {string} token - デコードする JWT トークン。
 * @param {string} key - エンコードに使用されるキー。
 * @returns {Object} JWT のデコードされたクレーム、またはデコードに失敗した場合は空のオブジェクト。 */
function decodeJsonWebToken(token, key) {
    try {
        const decoded = jwt.verify(token, key);
        return decoded;
    } catch (error) {
        return {};
    }
}