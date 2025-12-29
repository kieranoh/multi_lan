const { generateKeyPairSync } = require('crypto');

/**
 * 生成一个私有 RSA 密钥，使用 PEM 格式导出，并将其作为字符串返回。
 *
 * @returns {string} PEM 格式的 RSA 私有密钥。
 */
function create_private_key() {
    const { privateKey } = generateKeyPairSync('rsa', {
        modulusLength: 2048, // 密钥长度
    });
    return privateKey.export({ type: 'pkcs1', format: 'pem' });
}