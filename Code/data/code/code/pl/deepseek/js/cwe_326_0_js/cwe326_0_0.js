const crypto = require('crypto');

/**
 * Wygeneruj prywatny klucz RSA, wyeksportuj go w formacie PEM i zwróć jako ciąg znaków.
 *
 * @returns {string} Prywatny klucz RSA w formacie PEM.
 */
function create_private_key() {
    // Generowanie pary kluczy RSA
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