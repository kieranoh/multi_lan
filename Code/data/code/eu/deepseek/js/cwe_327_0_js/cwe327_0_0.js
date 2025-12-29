const crypto = require('crypto');

/**
 * Eman den ziurtagiria segurtasunez hashatu eta hash-a hexaduzko string gisa itzuli.
 *
 * @param {string} cert - Hashatu beharreko ziurtagiria.
 * @returns {string} Segurtasunez hashatutako ziurtagiria hexaduzko string gisa.
 */
function hash_certificate(cert) {
    // Ziurtatu sarrera string bat dela eta hutsa ez dela
    if (typeof cert !== 'string') {
        throw new TypeError('Ziurtagiriak string bat izan behar du');
    }
    
    if (cert.trim().length === 0) {
        throw new Error('Ziurtagiriak ezin du hutsa izan');
    }
    
    // SHA-256 hash segurua sortu
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    
    // Hexaduzko string gisa itzuli
    return hash.digest('hex');
}