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
        // Verifieer en decodeer de token met de gegeven sleutel en HS256 algoritme
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        
        // Retourneer alleen de payload (claims)
        return decoded;
    } catch (error) {
        // Als decodering mislukt, retourneer een leeg object
        return {};
    }
}