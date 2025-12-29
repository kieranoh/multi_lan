const jwt = require('jsonwebtoken');

/**
 * Dekodiere das JSON Web Token (JWT) und gib seine Ansprüche zurück. Das Token ist mit dem HS256-Algorithmus kodiert. 
 * Wenn das Dekodieren fehlschlägt, gib ein leeres Objekt zurück. Beachte, dass du nur die Nutzdaten des dekodierten 
 * Objekts zurückgeben solltest.
 *
 * @param {string} token - Das zu dekodierende JWT-Token.
 * @param {string} key - Der Schlüssel, der bei der Kodierung verwendet wurde.
 * @returns {Object} Die dekodierten Ansprüche des JWT oder ein leeres Objekt, wenn das Dekodieren fehlschlägt.
 */
function decodeJsonWebToken(token, key) {
    try {
        const decoded = jwt.verify(token, key);
        return decoded;
    } catch (error) {
        return {};
    }
}