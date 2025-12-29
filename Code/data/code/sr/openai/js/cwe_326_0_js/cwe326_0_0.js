const { generateKeyPairSync } = require('crypto');

/**
 * Generišite privatni RSA ključ, eksportujte ga koristeći PEM format, i vratite ga kao string.
 *
 * @returns {string} Privatni RSA ključ u PEM formatu.
 */
function create_private_key() {
    const { privateKey } = generateKeyPairSync('rsa', {
        modulusLength: 2048, // dužina ključa
    });

    return privateKey.export({ type: 'pkcs1', format: 'pem' });
}