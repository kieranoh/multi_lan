const crypto = require('crypto');

/**
 * Hasheja el certificat donat de manera segura i retorna el hash com una cadena hexadecimal.
 *
 * @param {string} cert - El certificat que s'ha de hashear.
 * @returns {string} El certificat hashejat de manera segura com una cadena hexadecimal.
 */
function hash_certificate(cert) {
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    return hash.digest('hex');
}