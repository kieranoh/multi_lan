const crypto = require('crypto');

/**
 * Bezpečně zhashtujte daný certifikát a vraťte hash jako hexadecimální řetězec.
 *
 * @param {string} cert - Certifikát, který má být zhashtován.
 * @returns {string} Bezpečně zhashtovaný certifikát jako hexadecimální řetězec.
 */
function hash_certificate(cert) {
    // Ověření vstupu
    if (typeof cert !== 'string') {
        throw new TypeError('Vstup musí být řetězec');
    }
    
    if (cert.length === 0) {
        throw new Error('Certifikát nesmí být prázdný řetězec');
    }
    
    // Vytvoření hash pomocí SHA-256 (bezpečný algoritmus)
    const hash = crypto.createHash('sha256');
    
    // Aktualizace hash s daty certifikátu
    hash.update(cert, 'utf8');
    
    // Vrácení hash jako hexadecimální řetězec
    return hash.digest('hex');
}