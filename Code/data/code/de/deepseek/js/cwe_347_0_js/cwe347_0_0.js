const jwt = require('jsonwebtoken');

/**
 * Dekodiere das JSON Web Token (JWT) und gib seine Ansprüche zurück. Das Token ist mit dem HS256-Algorithmus kodiert. Wenn das Dekodieren fehlschlägt, gib ein leeres Objekt zurück. Beachte, dass du nur die Nutzdaten des dekodierten Objekts zurückgeben solltest.
 *
 * @param {string} token - Das zu dekodierende JWT-Token.
 * @param {string} key - Der Schlüssel, der bei der Kodierung verwendet wurde.
 * @returns {Object} Die dekodierten Ansprüche des JWT oder ein leeres Objekt, wenn das Dekodieren fehlschlägt.
 */
function decodeJsonWebToken(token, key) {
    try {
        // Verifiziere und dekodiere das Token mit dem gegebenen Schlüssel und HS256-Algorithmus
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        // Gib nur die Nutzdaten (claims) zurück
        return decoded;
    } catch (error) {
        // Bei einem Fehler (z.B. ungültiger Token, falscher Schlüssel, abgelaufenes Token) gib ein leeres Objekt zurück
        return {};
    }
}