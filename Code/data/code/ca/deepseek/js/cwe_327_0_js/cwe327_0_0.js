const crypto = require('crypto');

/**
 * Hasheja el certificat donat de manera segura i retorna el hash com una cadena hexadecimal.
 *
 * @param {string} cert - El certificat que s'ha de hashear.
 * @returns {string} El certificat hashejat de manera segura com una cadena hexadecimal.
 */
function hash_certificate(cert) {
    // Validar que el certificat no estigui buit
    if (typeof cert !== 'string' || cert.trim().length === 0) {
        throw new Error('El certificat no pot estar buit');
    }

    // Crear un hash SHA-256 del certificat
    const hash = crypto.createHash('sha256');
    hash.update(cert, 'utf8');
    
    // Retornar el hash en format hexadecimal
    return hash.digest('hex');
}