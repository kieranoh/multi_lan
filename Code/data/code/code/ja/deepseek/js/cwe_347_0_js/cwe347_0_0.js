const jwt = require('jsonwebtoken');

/**
 * JSON Web Token (JWT) をデコードし、そのクレームを返します。トークンは HS256 アルゴリズムでエンコードされています。デコードに失敗した場合は、空のオブジェクトを返します。デコードされたもののペイロードのみを返すことに注意してください。
 *
 * @param {string} token - デコードする JWT トークン。
 * @param {string} key - エンコードに使用されるキー。
 * @returns {Object} JWT のデコードされたクレーム、またはデコードに失敗した場合は空のオブジェクト。
 */
function decodeJsonWebToken(token, key) {
    try {
        // jwt.verify を使用してトークンを検証し、ペイロードを取得します
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        // デコードされたオブジェクトからペイロード部分を返します
        // jwt.verify は通常、ペイロードを含むオブジェクトを返します
        return decoded;
    } catch (error) {
        // 検証に失敗した場合は空のオブジェクトを返します
        return {};
    }
}