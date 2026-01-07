const crypto = require('crypto');

/**
 * AES 및 CBC 모드를 사용하여 키로 데이터를 암호화합니다.
 * 제공된 키 바이트가 충분히 길어야 합니다 (>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
 * 암호화된 데이터, IV(초기화 벡터) 및 암호화에 사용된 키를 반환합니다.
 *
 * @param {Buffer} key - 암호화 키를 생성할 바이트 (최소 16 바이트).
 * @param {Buffer} data - 암호화할 데이터.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} 암호화된 데이터, IV 및 암호화에 사용된 키.
 */
function encrypt_data(key, data) {
    // Ensure the key is at least 16 bytes long
    if (key.length < 16) {
        throw new Error('키 길이는 최소 16 바이트이어야 합니다.');
    }

    // Generate a random initialization vector
    const iv = crypto.randomBytes(16);
    
    // Create a cipher using AES-256-CBC (adjust key length as needed)
    const cipher = crypto.createCipheriv('aes-256-cbc', key.slice(0, 32), iv);
    
    // Encrypt the data
    let encrypted = cipher.update(data, 'utf8', 'base64');
    encrypted += cipher.final('base64');
    
    // Return the encrypted data, iv, and the key used
    return {
        encryptedData: Buffer.from(encrypted, 'base64'),
        iv: iv,
        keyUsed: key.slice(0, 32)
    };
}