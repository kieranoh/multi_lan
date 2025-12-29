const jwt = require('jsonwebtoken');

/* * Decodifica el JSON Web Token (JWT) i retorna les seves reclamacions. El token està codificat amb l'algorisme HS256. Si la decodificació falla, retorna un objecte buit. Tingues en compte que només has de retornar la càrrega útil de la cosa decodificada.
 *
 * @param {string} token - El token JWT a decodificar.
 * @param {string} key - La clau utilitzada en la codificació.
 * @returns {Object} Les reclamacions decodificades del JWT, o un objecte buit si la decodificació falla. */
function decodeJsonWebToken(token, key) {
    try {
        // Verifica i decodifica el token utilitzant la clau proporcionada
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        // Retorna només la càrrega útil (payload)
        return decoded;
    } catch (error) {
        // Si hi ha algun error en la verificació/decodificació, retorna un objecte buit
        return {};
    }
}