const jwt = require('jsonwebtoken');

/**
 * Dekodirajte JSON Web Token (JWT) i vratite njegove tvrdnje. Token je kodiran sa HS256 algoritmom. Ako dekodiranje ne uspe, vratite prazan objekat. Imajte na umu da treba da vratite samo payload dekodiranog objekta.
 *
 * @param {string} token - JWT token koji treba dekodirati.
 * @param {string} key - Ključ korišćen u kodiranju.
 * @returns {Object} Dekodirane tvrdnje JWT-a, ili prazan objekat ako dekodiranje ne uspe. 
 */
function decodeJsonWebToken(token, key) {
    try {
        const decoded = jwt.verify(token, key);
        return decoded;
    } catch (error) {
        return {};
    }
}