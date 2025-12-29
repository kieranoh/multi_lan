const crypto = require('crypto');

/**
 * Hasha det angivna certifikatet på ett säkert sätt och returnera hashvärdet som en hexadecimalt sträng.
 *
 * @param {string} cert - Certifikatet som ska hashats.
 * @returns {string} Det säkert hashade certifikatet som en hexadecimalt sträng. 
 */
function hash_certificate(cert) {
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    return hash.digest('hex');
}