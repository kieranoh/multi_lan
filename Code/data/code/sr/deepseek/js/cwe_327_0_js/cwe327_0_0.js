const crypto = require('crypto');

/**
 * Sigurno haširajte dati sertifikat i vratite haš kao heksadecimalni string.
 *
 * @param {string} cert - Sertifikat koji treba haširati.
 * @returns {string} Sigurno haširani sertifikat kao heksadecimalni string.
 */
function hash_certificate(cert) {
    // Provera da li je sertifikat validan string
    if (typeof cert !== 'string') {
        throw new TypeError('Sertifikat mora biti string');
    }
    
    if (cert.trim().length === 0) {
        throw new Error('Sertifikat ne može biti prazan string');
    }
    
    // Uklanjanje eventualnih početnih i završnih belina
    const trimmedCert = cert.trim();
    
    // Kreiranje SHA-256 hash-a sertifikata
    const hash = crypto.createHash('sha256');
    hash.update(trimmedCert);
    
    // Vraćanje heksadecimalnog stringa
    return hash.digest('hex');
}