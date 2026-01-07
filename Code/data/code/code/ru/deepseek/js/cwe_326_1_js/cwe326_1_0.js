const crypto = require('crypto');

/**
 * Сгенерируйте закрытый ключ DSA, экспортируйте его в формате PEM и верните его в виде строки.
 *
 * @returns {string} Закрытый ключ DSA в формате PEM.
 */
function create_private_key_dsa() {
    // Генерируем параметры DSA (2048 бит, размер подгруппы 256 бит)
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