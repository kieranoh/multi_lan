const jwt = require('jsonwebtoken');

/**
 * Dekoda JSON Web Token (JWT) och returnera dess påståenden. Token är kodad med HS256-algoritmen. Om dekodningen misslyckas, returnera ett tomt objekt. Observera att du endast ska returnera nyttolasten av den dekodade saken.
 *
 * @param {string} token - JWT-token att dekoda.
 * @param {string} key - Nyckeln som används vid kodning.
 * @returns {Object} De dekodade påståendena av JWT, eller ett tomt objekt om dekodningen misslyckas.
 */
function decodeJsonWebToken(token, key) {
    try {
        // Verifiera och dekoda token med HS256-algoritmen
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        // Returnera endast nyttolasten (payload)
        return decoded;
    } catch (error) {
        // Om dekodningen misslyckas, returnera ett tomt objekt
        return {};
    }
}