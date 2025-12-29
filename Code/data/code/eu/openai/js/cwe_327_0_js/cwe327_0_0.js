const crypto = require('crypto');

/**
 * Eman den ziurtagiria segurtasunez hashatu eta hash-a hexaduzko string gisa itzuli.
 *
 * @param {string} cert - Hashatu beharreko ziurtagiria.
 * @returns {string} Segurtasunez hashatutako ziurtagiria hexaduzko string gisa.
 */
function hash_certificate(cert) {
    const hash = crypto.createHash('sha256'); // SHA-256 algoritmoa erabiltzen dugu
    hash.update(cert);
    return hash.digest('hex'); // Hash-a hexaduzko string gisa itzultzen dugu
}