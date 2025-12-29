const crypto = require('crypto');

/**
 * Wygeneruj prywatny klucz DSA, wyeksportuj go w formacie PEM i zwróć jako ciąg znaków.
 *
 * @returns {string} Prywatny klucz DSA w formacie PEM.
 */
function create_private_key_dsa() {
    // Generowanie pary kluczy DSA z parametrami 2048-bitowymi
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
    
    return privateKey;
}