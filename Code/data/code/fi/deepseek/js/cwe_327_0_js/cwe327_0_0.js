const crypto = require('crypto');

/**
 * Hashaa annettu sertifikaatti turvallisesti ja palauttaa hash heksadesimaalisena merkkijonona.
 *
 * @param {string} cert - Hashattava sertifikaatti.
 * @returns {string} Turvallisesti hashattu sertifikaatti heksadesimaalisena merkkijonona.
 */
function hash_certificate(cert) {
    // Tarkista, että sertifikaatti on annettu ja se on merkkijono
    if (typeof cert !== 'string') {
        throw new TypeError('Sertifikaatin tulee olla merkkijono');
    }
    
    if (cert.trim().length === 0) {
        throw new Error('Sertifikaatti ei voi olla tyhjä');
    }
    
    // Luo SHA-256 hash sertifikaatista
    const hash = crypto.createHash('sha256');
    hash.update(cert, 'utf8');
    
    // Palauta hash heksadesimaalimuodossa
    return hash.digest('hex');
}