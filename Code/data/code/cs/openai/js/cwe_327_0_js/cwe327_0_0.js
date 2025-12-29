const crypto = require('crypto');

/**
 * Bezpečně zhashtujte daný certifikát a vraťte hash jako hexadecimální řetězec.
 *
 * @param {string} cert - Certifikát, který má být zhashtován.
 * @returns {string} Bezpečně zhashtovaný certifikát jako hexadecimální řetězec.
 */
function hash_certificate(cert) {
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    return hash.digest('hex');
}