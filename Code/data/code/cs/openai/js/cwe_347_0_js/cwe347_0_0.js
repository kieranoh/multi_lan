const jwt = require('jsonwebtoken');

/**
 * Dekódujte JSON Web Token (JWT) a vraťte jeho nároky. Token je zakódován pomocí algoritmu HS256. 
 * Pokud dekódování selže, vraťte prázdný objekt. Všimněte si, že byste měli vrátit pouze payload dekódované věci.
 *
 * @param {string} token - JWT token k dekódování.
 * @param {string} key - Klíč použitý při kódování.
 * @returns {Object} Dekódované nároky JWT, nebo prázdný objekt, pokud dekódování selže. 
 */
function decodeJsonWebToken(token, key) {
    try {
        const decoded = jwt.verify(token, key);
        return decoded; // Vraťte pouze payload dekódované věci
    } catch (error) {
        return {}; // Pokud dekódování selže, vraťte prázdný objekt
    }
}