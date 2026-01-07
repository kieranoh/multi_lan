const crypto = require('crypto');

/**
 * Сгенерируйте закрытый ключ DSA, экспортируйте его в формате PEM и верните его в виде строки.
 *
 * @returns {string} Закрытый ключ DSA в формате PEM.
 */
function create_private_key_dsa() {
    const { generateKeyPairSync } = crypto;
    const { privateKey } = generateKeyPairSync('dsa', {
        modulusLength: 2048, // длина ключа в битах
        privateKeyEncoding: {
            type: 'spki',
            format: 'pem'
        }
    });
    return privateKey;
}