const { generateKeyPairSync } = require('crypto');

/**
 * Wygeneruj prywatny klucz RSA, wyeksportuj go w formacie PEM i zwróć jako ciąg znaków.
 *
 * @returns {string} Prywatny klucz RSA w formacie PEM.
 */
function create_private_key() {
    const { privateKey } = generateKeyPairSync('rsa', {
        modulusLength: 2048,
    });

    // Eksportowanie klucza prywatnego w formacie PEM
    return privateKey.export({ type: 'spki', format: 'pem' });
}