const crypto = require('crypto');

/**
 * Сгенерируйте закрытый ключ RSA, экспортируйте его в формате PEM и верните его в виде строки.
 *
 * @returns {string} Закрытый ключ RSA в формате PEM.
 */
function create_private_key() {
    // Генерация пары ключей RSA с длиной 2048 бит (стандартная безопасная длина)
    const { privateKey } = crypto.generateKeyPairSync('rsa', {
        modulusLength: 2048,
        publicKeyEncoding: {
            type: 'spki',
            format: 'pem'
        },
        privateKeyEncoding: {
            type: 'pkcs8', // PKCS#8 формат для закрытого ключа
            format: 'pem'
        }
    });
    
    return privateKey;
}