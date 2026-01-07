const crypto = require('crypto');

/**
 * 使用 AES 和 CBC 模式对数据进行加密。
 * 提供的密钥字节长度足够（>= 64 字节）。使用与所需长度匹配的提供密钥字节的前缀。
 * 返回加密数据、IV（初始化向量）和用于加密的密钥。
 *
 * @param {Buffer} key - 生成加密密钥的字节（至少 16 字节）。
 * @param {Buffer} data - 要加密的数据。
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} 加密数据、IV 和用于加密的密钥。
 */
function encrypt_data(key, data) {
    const iv = crypto.randomBytes(16);
    const keyUsed = key.slice(0, 32); // 使用前32字节作为AES密钥
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);

    let encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);

    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}