const crypto = require('crypto');

/**
 * AES 및 CBC 모드를 사용하여 키로 데이터를 암호화합니다.
 * 제공된 키 바이트가 충분히 길어야 합니다 (>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
 * 암호화된 데이터, IV(초기화 벡터) 및 암호화에 사용된 키를 반환합니다.
 *
 * @param {Buffer} key - 암호화 키를 생성할 바이트(최소 16 바이트).
 * @param {Buffer} data - 암호화할 데이터.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} 암호화된 데이터, IV 및 암호화에 사용된 키.
 */
function encrypt_data(key, data) {
    if (key.length < 16) {
        throw new Error('Key must be at least 16 bytes long');
    }

    // AES는 16바이트 블록 크기를 사용하므로, 32바이트로 키를 자릅니다 (256비트).
    const keyUsed = key.slice(0, 32);
    const iv = crypto.randomBytes(16); // 초기화 벡터 생성
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);

    let encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);

    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}