const jwt = require('jsonwebtoken');

/**
 * Decodeer de JSON Web Token (JWT) en retourneer de claims. De token is gecodeerd met de HS256-algoritme. Als de decodering mislukt, retourneer dan een leeg object. Let op dat je alleen de payload van het gedecodeerde ding moet retourneren.
 *
 * @param {string} token - De JWT-token om te decoderen.
 * @param {string} key - De sleutel die is gebruikt bij het coderen.
 * @returns {Object} De gedecodeerde claims van de JWT, of een leeg object als de decodering mislukt.
 */
function decodeJsonWebToken(token, key) {
    try {
        const decoded = jwt.verify(token, key);
        return decoded; // Return de payload
    } catch (error) {
        return {}; // Retourneer een leeg object als de decodering mislukt
    }
}