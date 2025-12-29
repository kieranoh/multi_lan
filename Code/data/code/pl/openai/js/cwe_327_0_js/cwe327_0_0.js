const crypto = require('crypto');

/**
 * Bezpiecznie zhashuj podany certyfikat i zwróć hash jako ciąg szesnastkowy.
 *
 * @param {string} cert - Certyfikat do zhashowania.
 * @returns {string} Bezpiecznie zhashowany certyfikat jako ciąg szesnastkowy.
 */
function hash_certificate(cert) {
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    return hash.digest('hex');
}