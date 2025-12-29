const crypto = require('crypto');

/**
 * Genereer een privésleutel voor DSA, exporteer deze in het PEM-formaat en geef deze terug als een string.
 *
 * @returns {string} De DSA privésleutel in PEM-formaat.
 */
function create_private_key_dsa() {
    // Genereer DSA-sleutelparameters (2048 bits is een gangbare veilige grootte)
    const keyPair = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048,
        divisorLength: 256, // q parameter grootte (moet 160, 224 of 256 bits zijn voor DSA)
        publicKeyEncoding: {
            type: 'spki',
            format: 'pem'
        },
        privateKeyEncoding: {
            type: 'pkcs8',
            format: 'pem'
        }
    });
    
    // Retourneer de privésleutel in PEM-formaat
    return keyPair.privateKey;
}