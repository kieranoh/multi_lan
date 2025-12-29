const crypto = require('crypto');

/**
 * Hashea el certificado dado de forma segura y devuelve el hash como una cadena hexadecimal.
 *
 * @param {string} cert - El certificado que se va a hashear.
 * @returns {string} El certificado hasheado de forma segura como una cadena hexadecimal.
 */
function hash_certificate(cert) {
    if (typeof cert !== 'string') {
        throw new TypeError('El certificado debe ser una cadena de texto');
    }
    
    if (cert.trim().length === 0) {
        throw new Error('El certificado no puede estar vacío');
    }
    
    // Crear un hash SHA-256 del certificado
    const hash = crypto.createHash('sha256');
    hash.update(cert, 'utf8');
    
    // Devolver el hash en formato hexadecimal
    return hash.digest('hex');
}