const crypto = require('crypto');

/**
 * Sigurno hashirajte danu potvrdu i vratite hash kao heksadecimalni niz.
 *
 * @param {string} cert - Potvrda koja se treba hashirati.
 * @returns {string} Sigurno hashirana potvrda kao heksadecimalni niz.
 */
function hash_certificate(cert) {
    // Provjeri je li cert string
    if (typeof cert !== 'string') {
        throw new TypeError('Ulaz mora biti string');
    }

    // Provjeri je li cert prazan
    if (cert.length === 0) {
        throw new Error('Ulaz ne smije biti prazan string');
    }

    // Koristi SHA-256 za sigurno hashiranje
    const hash = crypto.createHash('sha256');
    hash.update(cert, 'utf8');
    
    // Vrati hash kao heksadecimalni niz
    return hash.digest('hex');
}