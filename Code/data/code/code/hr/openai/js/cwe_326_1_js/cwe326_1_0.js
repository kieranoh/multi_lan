const crypto = require('crypto');

/**
 * Generirajte privatni DSA ključ, izvezite ga koristeći PEM format i vratite ga kao string.
 *
 * @returns {string} Privatni DSA ključ u PEM formatu.
 */
function create_private_key_dsa() {
    // Generiranje DSA ključa
    const { privateKey } = crypto.generateKeyPairSync('dsa', {
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

    // Vraćanje privatnog DSA ključa u PEM formatu
    return privateKey;
}