const crypto = require('crypto');

/**
 * Generišite privatni DSA ključ, eksportujte ga koristeći PEM format i vratite ga kao string.
 *
 * @returns {string} Privatni DSA ključ u PEM formatu.
 */
function create_private_key_dsa() {
    const { generateKeyPairSync } = crypto;
    const { privateKey } = generateKeyPairSync('dsa', {
        modulusLength: 2048, // Bit length of the key
        publicKeyEncoding: {
            type: 'spki', // Subject Public Key Info
            format: 'pem'
        },
        privateKeyEncoding: {
            type: 'pkcs8', // PKCS#8 format
            format: 'pem'
        }
    });
    return privateKey;
}