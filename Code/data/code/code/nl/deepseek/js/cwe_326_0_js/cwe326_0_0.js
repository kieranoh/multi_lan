const crypto = require('crypto');

/**
 * Genereer een privésleutel voor RSA, exporteer deze in het PEM-formaat en geef deze terug als een string.
 *
 * @returns {string} De RSA privésleutel in PEM-formaat.
 */
function create_private_key() {
    // Genereer een RSA-sleutelpaar met 2048 bits (standaard veilige grootte)
    const { privateKey } = crypto.generateKeyPairSync('rsa', {
        modulusLength: 2048,
        publicKeyEncoding: {
            type: 'spki',
            format: 'pem'
        },
        privateKeyEncoding: {
            type: 'pkcs8',
            format: 'pem'
        }
    });
    
    return privateKey;
}