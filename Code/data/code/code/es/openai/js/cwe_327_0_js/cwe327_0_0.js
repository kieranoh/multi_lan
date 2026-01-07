const crypto = require('crypto');

/**
 * Hashea el certificado dado de forma segura y devuelve el hash como una cadena hexadecimal.
 *
 * @param {string} cert - El certificado que se va a hashear.
 * @returns {string} El certificado hasheado de forma segura como una cadena hexadecimal.
 */
function hash_certificate(cert) {
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    return hash.digest('hex');
}