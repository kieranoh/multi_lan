const jwt = require('jsonwebtoken');

/**
 * Zdekoduj token JSON Web Token (JWT) i zwróć jego roszczenia. Token jest zakodowany algorytmem HS256. Jeśli dekodowanie się nie powiedzie, zwróć pusty obiekt. Zauważ, że powinieneś zwrócić tylko ładunek zdekodowanej rzeczy.
 *
 * @param {string} token - Token JWT do zdekodowania.
 * @param {string} key - Klucz użyty do kodowania.
 * @returns {Object} Zdekodowane roszczenia JWT lub pusty obiekt, jeśli dekodowanie się nie powiedzie.
 */
function decodeJsonWebToken(token, key) {
    try {
        // Weryfikacja tokenu przy użyciu podanego klucza i algorytmu HS256
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        // Zwróć tylko ładunek (payload) zdekodowanego tokenu
        return decoded;
    } catch (error) {
        // W przypadku błędu weryfikacji (np. nieprawidłowy token, wygasły token, nieprawidłowy klucz)
        // zwróć pusty obiekt
        return {};
    }
}