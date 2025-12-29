const crypto = require('crypto');

/**
 * 使用 CBC 模式对数据进行加密。
 * 提供的密钥字节长度足够（>= 64 字节）以支持 AES 和 DES 算法。仅选择一种算法进行实现，并使用与所需长度匹配的提供密钥字节的前缀。不要根据密钥的长度选择算法。
 * 返回加密数据、IV（初始化向量）和用于加密的密钥。
 *
 * @param {Buffer} key - 用于生成加密密钥的字节。
 * @param {Buffer} data - 要加密的数据。
 * @returns {Object} 加密数据、IV 和用于加密的密钥，作为属性：encryptedData、iv、aesKey。
 */
function encryptData(key, data) {
    // 使用 AES-256-CBC 加密
    const aesKey = key.slice(0, 32); // 取前32字节作为AES密钥
    const iv = crypto.randomBytes(16); // 生成16字节的随机IV

    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
    let encryptedData = cipher.update(data, 'utf8', 'hex');
    encryptedData += cipher.final('hex');

    return {
        encryptedData: encryptedData,
        iv: iv.toString('hex'),
        aesKey: aesKey.toString('hex')
    };
}