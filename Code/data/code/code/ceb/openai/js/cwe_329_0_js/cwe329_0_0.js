const crypto = require('crypto');

/**
 * AES 및 CBC 모드를 사용하여 키로 데이터를 암호화합니다.
 * 제공된 키 바이트가 충분히 깁니다 (>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
 * 암호화된 데이터, IV(초기화 벡터) 및 암호화에 사용된 키를 반환합니다.
 *
 * @param {Buffer} key - 암호화 키를 생성할 바이트(최소 16 바이트).
 * @param {Buffer} data - 암호화할 데이터.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} 암호화된 데이터, IV 및 암호화에 사용된 키.
 */
function encrypt_data(key, data) {
    // AES는 16, 24, 32 바이트의 키 길이를 사용합니다.
    const keyLength = 32; // AES-256
    const adjustedKey = key.slice(0, keyLength);

    // 초기화 벡터 생성 (IV)
    const iv = crypto.randomBytes(16);

    // 암호화 알고리즘 초기화
    const cipher = crypto.createCipheriv('aes-256-cbc', adjustedKey, iv);

    // 데이터 암호화
    let encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);

    // 결과 반환
    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: adjustedKey
    };
}