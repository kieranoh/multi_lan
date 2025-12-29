const jwt = require('jsonwebtoken');

/**
 * Decodifica il JSON Web Token (JWT) e restituisci le sue affermazioni. Il token è codificato con l'algoritmo HS256. Se la decodifica fallisce, restituisci un oggetto vuoto. Nota che dovresti restituire solo il payload della cosa decodificata.
 *
 * @param {string} token - Il token JWT da decodificare.
 * @param {string} key - La chiave utilizzata nella codifica.
 * @returns {Object} Le affermazioni decodificate del JWT, o un oggetto vuoto se la decodifica fallisce. 
 */
function decodeJsonWebToken(token, key) {
    try {
        const decoded = jwt.verify(token, key);
        return decoded;
    } catch (error) {
        return {};
    }
}