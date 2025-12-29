const jwt = require('jsonwebtoken');

/**
 * Dekódolja a JSON Web Tokent (JWT) és adja vissza annak állításait. A tokent az HS256 algoritmussal kódolták. Ha a dekódolás nem sikerül, adjon vissza egy üres objektumot. Ne feledje, hogy csak a dekódolt dolog payload-ját kell visszaadnia.
 *
 * @param {string} token - A dekódolandó JWT token.
 * @param {string} key - A kódolás során használt kulcs.
 * @returns {Object} A JWT dekódolt állításai, vagy egy üres objektum, ha a dekódolás nem sikerül.
 */
function decodeJsonWebToken(token, key) {
    try {
        const decoded = jwt.verify(token, key);
        return decoded;
    } catch (error) {
        return {};
    }
}