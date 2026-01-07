const { generateKeyPairSync } = require('crypto');

/**
 * Wygeneruj prywatny klucz DSA, wyeksportuj go w formacie PEM i zwróć jako ciąg znaków.
 *
 * @returns {string} Prywatny klucz DSA w formacie PEM.
 */
function create_private_key_dsa() {
    const { privateKey } = generateKeyPairSync('dsa', {
        modulusLength: 2048, // Modulus length for DSA keys
        publicKeyEncoding: {
            type: 'spki', // Public Key Info
            format: 'pem',
        },
        privateKeyEncoding: {
            type: 'pkcs8', // Private Key Info
            format: 'pem',
        }
    });
    
    return privateKey;
}