/**
 * Hashaa annettu sertifikaatti turvallisesti ja palauta hash heksadesimaalisena merkkijonona.
 *
 * @param {string} cert - Hashattava sertifikaatti.
 * @returns {string} Turvallisesti hashattu sertifikaatti heksadesimaalisena merkkijonona.
 */
function hash_certificate(cert) {
    const crypto = require('crypto');
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    return hash.digest('hex');
}