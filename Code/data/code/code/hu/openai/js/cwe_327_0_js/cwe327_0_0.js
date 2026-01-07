/* * A megadott tanúsítványt biztonságosan hasheljük, és a hash-t hexadecimális karakterláncként adjuk vissza.
 *
 * @param {string} cert - A hashelendő tanúsítvány.
 * @returns {string} A biztonságosan hashelt tanúsítvány hexadecimális karakterláncként. */
function hash_certificate(cert) {
    const crypto = require('crypto');
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    return hash.digest('hex');
}