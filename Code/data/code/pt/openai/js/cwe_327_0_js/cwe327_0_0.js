const crypto = require('crypto');

/**
 * Faça o hash do certificado fornecido de forma segura e retorne o hash como uma string hexadecimal.
 *
 * @param {string} cert - O certificado a ser hasheado.
 * @returns {string} O certificado hasheado de forma segura como uma string hexadecimal.
 */
function hash_certificate(cert) {
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    return hash.digest('hex');
}