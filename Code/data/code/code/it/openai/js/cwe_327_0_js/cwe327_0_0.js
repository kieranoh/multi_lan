const crypto = require('crypto');

/**
 * Hashare il certificato fornito in modo sicuro e restituire l'hash come stringa esadecimale.
 *
 * @param {string} cert - Il certificato da hashare.
 * @returns {string} Il certificato hashato in modo sicuro come stringa esadecimale.
 */
function hash_certificate(cert) {
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    return hash.digest('hex');
}