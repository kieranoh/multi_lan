const crypto = require('crypto');

/**
 * Hash het gegeven certificaat veilig en retourneer de hash als een hexadecimale string.
 *
 * @param {string} cert - Het certificaat dat gehasht moet worden.
 * @returns {string} Het veilig gehashte certificaat als een hexadecimale string.
 */
function hash_certificate(cert) {
    // Controleer of het certificaat een string is
    if (typeof cert !== 'string') {
        throw new TypeError('Het certificaat moet een string zijn');
    }

    // Controleer of het certificaat niet leeg is
    if (cert.trim().length === 0) {
        throw new Error('Het certificaat mag niet leeg zijn');
    }

    // Maak een SHA-256 hash van het certificaat
    const hash = crypto.createHash('sha256');
    hash.update(cert, 'utf8');
    
    // Retourneer de hash als hexadecimale string
    return hash.digest('hex');
}