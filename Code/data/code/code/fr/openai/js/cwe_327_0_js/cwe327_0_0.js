const crypto = require('crypto');

/**
 * Hachez le certificat donné de manière sécurisée et renvoyez le hachage sous forme de chaîne hexadécimale.
 *
 * @param {string} cert - Le certificat à hacher.
 * @returns {string} Le certificat haché de manière sécurisée sous forme de chaîne hexadécimale.
 */
function hash_certificate(cert) {
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    return hash.digest('hex');
}