const jwt = require('jsonwebtoken');

/* * Dekodirajte JSON Web Token (JWT) i vratite njegove tvrdnje. Token je kodiran s HS256 algoritmom. Ako dekodiranje ne uspije, vratite prazan objekt. Imajte na umu da trebate vratiti samo payload dekodiranog objekta.
 *
 * @param {string} token - JWT token za dekodiranje.
 * @param {string} key - Ključ korišten u kodiranju.
 * @returns {Object} Dekodirane tvrdnje JWT-a, ili prazan objekt ako dekodiranje ne uspije. */
function decodeJsonWebToken(token, key) {
    try {
        const decoded = jwt.verify(token, key);
        return decoded;
    } catch (error) {
        return {};
    }
}