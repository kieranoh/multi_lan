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
    // 选择 AES-256-CBC 算法（固定选择，不根据密钥长度选择）
    const algorithm = 'aes-256-cbc';
    const keyLength = 32; // AES-256 需要 32 字节密钥
    
    // 检查密钥长度是否足够
    if (key.length < keyLength) {
        throw new Error(`密钥长度不足，需要至少 ${keyLength} 字节，但只有 ${key.length} 字节`);
    }
    
    // 使用密钥的前 keyLength 字节作为 AES 密钥
    const aesKey = key.slice(0, keyLength);
    
    // 生成随机初始化向量（IV）
    const iv = crypto.randomBytes(16); // AES CBC 需要 16 字节 IV
    
    // 创建加密器
    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    
    // 加密数据
    let encryptedData = cipher.update(data);
    encryptedData = Buffer.concat([encryptedData, cipher.final()]);
    
    // 返回结果对象
    return {
        encryptedData: encryptedData,
        iv: iv,
        aesKey: aesKey
    };
}