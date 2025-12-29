const crypto = require('crypto');

/**
 * Hash het gegeven certificaat veilig en retourneer de hash als een hexadecimale string.
 *
 * @param {string} cert - Het certificaat dat gehasht moet worden.
 * @returns {string} Het veilig gehashte certificaat als een hexadecimale string.
 */
function hash_certificate(cert) {
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    return hash.digest('hex');
}