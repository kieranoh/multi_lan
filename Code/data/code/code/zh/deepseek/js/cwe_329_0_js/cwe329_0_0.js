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
    // 验证输入参数
    if (!Buffer.isBuffer(key) || !Buffer.isBuffer(data)) {
        throw new TypeError('key 和 data 必须是 Buffer 类型');
    }
    
    if (key.length < 16) {
        throw new Error('key 必须至少为 16 字节');
    }
    
    // 对于 AES-CBC，密钥长度可以是 16、24 或 32 字节（对应 AES-128、AES-192、AES-256）
    // 根据提供的密钥长度选择合适的密钥长度
    let keyLength;
    if (key.length >= 32) {
        keyLength = 32; // AES-256
    } else if (key.length >= 24) {
        keyLength = 24; // AES-192
    } else {
        keyLength = 16; // AES-128
    }
    
    // 使用密钥的前 keyLength 字节作为加密密钥
    const keyUsed = key.slice(0, keyLength);
    
    // 生成随机的 16 字节 IV（初始化向量）
    const iv = crypto.randomBytes(16);
    
    // 创建 AES-CBC 加密器
    const cipher = crypto.createCipheriv('aes-' + (keyLength * 8) + '-cbc', keyUsed, iv);
    
    // 加密数据
    let encryptedData = cipher.update(data);
    encryptedData = Buffer.concat([encryptedData, cipher.final()]);
    
    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}