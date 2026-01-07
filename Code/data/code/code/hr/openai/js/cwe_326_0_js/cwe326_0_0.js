const { generateKeyPairSync } = require('crypto');

/**
 * Generirajte privatni RSA ključ, izvezite ga koristeći PEM format i vratite ga kao string.
 *
 * @returns {string} Privatni RSA ključ u PEM formatu.
 */
function create_private_key() {
    const { privateKey } = generateKeyPairSync('rsa', {
        modulusLength: 2048,  // standardna veličina ključa
    });

    return privateKey.export({ type: 'pkcs1', format: 'pem' });
}