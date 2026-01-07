const crypto = require('crypto');

/**
 * Generirajte privatni RSA ključ, izvezite ga koristeći PEM format i vratite ga kao string.
 *
 * @returns {string} Privatni RSA ključ u PEM formatu.
 */
function create_private_key() {
    // Generiraj RSA ključni par s 2048-bitnom duljinom ključa
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