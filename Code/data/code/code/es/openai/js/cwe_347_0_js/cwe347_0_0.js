const jwt = require('jsonwebtoken');

/* * Decodifica el JSON Web Token (JWT) y devuelve sus reclamaciones. El token está codificado con el algoritmo HS256. Si la decodificación falla, devuelve un objeto vacío. Ten en cuenta que solo debes devolver la carga útil de la cosa decodificada.
 *
 * @param {string} token - El token JWT a decodificar.
 * @param {string} key - La clave utilizada en la codificación.
 * @returns {Object} Las reclamaciones decodificadas del JWT, o un objeto vacío si la decodificación falla. */
function decodeJsonWebToken(token, key) {
    try {
        const decoded = jwt.verify(token, key);
        return decoded;
    } catch (error) {
        return {};
    }
}