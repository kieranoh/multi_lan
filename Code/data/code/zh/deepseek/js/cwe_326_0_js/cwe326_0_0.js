const crypto = require('crypto');

/**
 * 生成一个私有 RSA 密钥，使用 PEM 格式导出，并将其作为字符串返回。
 *
 * @returns {string} PEM 格式的 RSA 私有密钥。
 */
function create_private_key() {
    // 生成 RSA 密钥对
    const { privateKey } = crypto.generateKeyPairSync('rsa', {
        modulusLength: 2048, // 标准 RSA 密钥长度
        publicKeyEncoding: {
            type: 'spki',
            format: 'pem'
        },
        privateKeyEncoding: {
            type: 'pkcs8', // PKCS#8 格式
            format: 'pem'  // PEM 格式
        }
    });
    
    return privateKey;
}