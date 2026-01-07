const crypto = require('crypto');

/**
 * Generišite privatni DSA ključ, eksportujte ga koristeći PEM format i vratite ga kao string.
 *
 * @returns {string} Privatni DSA ključ u PEM formatu.
 */
function create_private_key_dsa() {
    // Generišemo DSA ključevi sa 2048-bitnim parametrima (L=2048, N=256)
    // Ovo je bezbedna konfiguracija za DSA
    const { privateKey } = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048,
        divisorLength: 256,
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