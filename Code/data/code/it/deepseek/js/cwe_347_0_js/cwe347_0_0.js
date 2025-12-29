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
        // Verifica e decodifica il token usando la chiave e l'algoritmo specificato
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        
        // Restituisce solo il payload del token decodificato
        return decoded;
    } catch (error) {
        // Se la decodifica fallisce, restituisce un oggetto vuoto
        return {};
    }
}