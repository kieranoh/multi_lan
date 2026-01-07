const crypto = require('crypto');

/**
 * Sigurno hashirajte danu potvrdu i vratite hash kao heksadecimalni niz.
 *
 * @param {string} cert - Potvrda koja se treba hashirati.
 * @returns {string} Sigurno hashirana potvrda kao heksadecimalni niz.
 */
function hash_certificate(cert) {
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    return hash.digest('hex');
}