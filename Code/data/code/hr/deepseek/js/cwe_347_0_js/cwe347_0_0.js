const jwt = require('jsonwebtoken');

/**
 * Dekodirajte JSON Web Token (JWT) i vratite njegove tvrdnje. Token je kodiran s HS256 algoritmom.
 * Ako dekodiranje ne uspije, vratite prazan objekt. Imajte na umu da trebate vratiti samo payload dekodiranog objekta.
 *
 * @param {string} token - JWT token za dekodiranje.
 * @param {string} key - Ključ korišten u kodiranju.
 * @returns {Object} Dekodirane tvrdnje JWT-a, ili prazan objekt ako dekodiranje ne uspije.
 */
function decodeJsonWebToken(token, key) {
    try {
        // Verificirajte token s danim ključem i HS256 algoritmom
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        // Vratite samo payload dio
        return decoded;
    } catch (error) {
        // Ako verificiranje ne uspije, vratite prazan objekt
        return {};
    }
}