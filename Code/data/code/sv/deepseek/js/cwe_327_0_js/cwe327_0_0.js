const crypto = require('crypto');

/**
 * Hasha det angivna certifikatet på ett säkert sätt och returnera hashvärdet som en hexadecimalt sträng.
 *
 * @param {string} cert - Certifikatet som ska hashats.
 * @returns {string} Det säkert hashade certifikatet som en hexadecimalt sträng.
 */
function hash_certificate(cert) {
    // Validera att certifikatet inte är tomt
    if (typeof cert !== 'string' || cert.trim().length === 0) {
        throw new Error('Certifikatet måste vara en icke-tom sträng');
    }

    // Skapa en SHA-256 hash av certifikatet
    const hash = crypto.createHash('sha256');
    hash.update(cert, 'utf8');
    
    // Returnera hashvärdet som en hexadecimal sträng
    return hash.digest('hex');
}