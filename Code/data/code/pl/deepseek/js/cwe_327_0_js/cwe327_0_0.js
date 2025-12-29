const crypto = require('crypto');

/**
 * Bezpiecznie zhashuj podany certyfikat i zwróć hash jako ciąg szesnastkowy.
 *
 * @param {string} cert - Certyfikat do zhashowania.
 * @returns {string} Bezpiecznie zhashowany certyfikat jako ciąg szesnastkowy.
 */
function hash_certificate(cert) {
    // Sprawdź, czy certyfikat jest niepustym ciągiem
    if (typeof cert !== 'string' || cert.trim().length === 0) {
        throw new Error('Certyfikat musi być niepustym ciągiem znaków');
    }

    // Utwórz hash SHA-256 z certyfikatu
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    
    // Zwróć hash jako ciąg szesnastkowy
    return hash.digest('hex');
}