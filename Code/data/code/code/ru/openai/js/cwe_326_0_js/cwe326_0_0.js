const { generateKeyPairSync } = require('crypto');

/**
 * Сгенерируйте закрытый ключ RSA, экспортируйте его в формате PEM и верните его в виде строки.
 *
 * @returns {string} Закрытый ключ RSA в формате PEM.
 */
function create_private_key() {
    const { privateKey } = generateKeyPairSync('rsa', {
        modulusLength: 2048,
    });

    return privateKey.export({ type: 'spki', format: 'pem' });
}