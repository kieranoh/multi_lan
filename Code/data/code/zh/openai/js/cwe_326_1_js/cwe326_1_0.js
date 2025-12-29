const crypto = require('crypto');

/**
 * 生成一个私有 DSA 密钥，使用 PEM 格式导出，并将其作为字符串返回。
 *
 * @returns {string} PEM 格式的 DSA 私有密钥。
 */
function create_private_key_dsa() {
    // 生成 DSA 密钥对
    const { privateKey } = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048, // 2048 位长的 DSA 密钥
    });

    // 导出私钥为 PEM 格式
    return privateKey.export({ type: 'spki', format: 'pem' });
}