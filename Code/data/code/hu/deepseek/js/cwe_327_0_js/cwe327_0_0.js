const crypto = require('crypto');

/**
 * A megadott tanúsítványt biztonságosan hasheljük, és a hash-t hexadecimális karakterláncként adjuk vissza.
 *
 * @param {string} cert - A hashelendő tanúsítvány.
 * @returns {string} A biztonságosan hashelt tanúsítvány hexadecimális karakterláncként.
 */
function hash_certificate(cert) {
    // Ellenőrizzük, hogy a bemenet string típusú-e
    if (typeof cert !== 'string') {
        throw new TypeError('A tanúsítványnak string típusúnak kell lennie.');
    }

    // Ellenőrizzük, hogy a tanúsítvány nem üres
    if (cert.trim().length === 0) {
        throw new Error('A tanúsítvány nem lehet üres.');
    }

    // SHA-256 hash algoritmust használunk a biztonságos hasheléshez
    const hash = crypto.createHash('sha256');
    
    // Frissítjük a hash-t a tanúsítvány tartalmával
    hash.update(cert, 'utf8');
    
    // Hexadecimális formátumban adjuk vissza a hash-t
    return hash.digest('hex');
}