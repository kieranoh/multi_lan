const crypto = require('crypto');

/**
 * 生成一个私有 DSA 密钥，使用 PEM 格式导出，并将其作为字符串返回。
 *
 * @returns {string} PEM 格式的 DSA 私有密钥。
 */
function create_private_key_dsa() {
    // 使用 Node.js 的 crypto 模块生成 DSA 密钥对
    const { privateKey } = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048, // DSA 密钥长度，通常为 1024、2048 或 3072 位
    });
    
    // 将私钥导出为 PEM 格式的字符串
    const privateKeyPem = privateKey.export({
        format: 'pem',
        type: 'pkcs8'
    });
    
    return privateKeyPem;
}