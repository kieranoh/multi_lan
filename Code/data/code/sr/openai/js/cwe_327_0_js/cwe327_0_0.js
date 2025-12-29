const crypto = require('crypto');

/**
 * Sigurno haširajte dati sertifikat i vratite haš kao heksadecimalni string.
 *
 * @param {string} cert - Sertifikat koji treba haširati.
 * @returns {string} Sigurno haširani sertifikat kao heksadecimalni string.
 */
function hash_certificate(cert) {
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    return hash.digest('hex');
}