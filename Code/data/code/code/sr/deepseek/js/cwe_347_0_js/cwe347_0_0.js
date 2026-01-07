const jwt = require('jsonwebtoken');

/**
 * Dekodirajte JSON Web Token (JWT) i vratite njegove tvrdnje. Token je kodiran sa HS256 algoritmom. 
 * Ako dekodiranje ne uspe, vratite prazan objekat. Imajte na umu da treba da vratite samo payload dekodiranog objekta.
 *
 * @param {string} token - JWT token koji treba dekodirati.
 * @param {string} key - Ključ korišćen u kodiranju.
 * @returns {Object} Dekodirane tvrdnje JWT-a, ili prazan objekat ako dekodiranje ne uspe.
 */
function decodeJsonWebToken(token, key) {
    try {
        // Verifikujemo token sa datim ključem i HS256 algoritmom
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        // Vraćamo samo payload deo
        return decoded;
    } catch (error) {
        // Ako dekodiranje/verifikacija ne uspe, vraćamo prazan objekat
        return {};
    }
}