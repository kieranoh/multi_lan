const crypto = require('crypto');

/**
 * Hashare il certificato fornito in modo sicuro e restituire l'hash come stringa esadecimale.
 *
 * @param {string} cert - Il certificato da hashare.
 * @returns {string} Il certificato hashato in modo sicuro come stringa esadecimale.
 */
function hash_certificate(cert) {
    // Validazione dell'input
    if (typeof cert !== 'string') {
        throw new TypeError('Il certificato deve essere una stringa');
    }
    
    if (cert.length === 0) {
        throw new Error('Il certificato non può essere vuoto');
    }
    
    // Creazione dell'hash SHA-256 (considerato sicuro per questo scopo)
    const hash = crypto.createHash('sha256');
    
    // Aggiornamento dell'hash con il certificato
    hash.update(cert, 'utf8');
    
    // Restituzione dell'hash come stringa esadecimale
    return hash.digest('hex');
}