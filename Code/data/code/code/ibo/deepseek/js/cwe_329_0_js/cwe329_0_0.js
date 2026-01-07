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
    // 키 길이 검증
    if (!Buffer.isBuffer(key) || key.length < 16) {
        throw new Error('키는 최소 16바이트의 Buffer여야 합니다.');
    }
    
    if (!Buffer.isBuffer(data)) {
        throw new Error('데이터는 Buffer여야 합니다.');
    }
    
    // AES-256-CBC를 사용하므로 32바이트 키가 필요합니다
    const KEY_LENGTH = 32;
    
    // 제공된 키에서 필요한 길이만큼 접두사를 사용합니다
    const keyUsed = key.slice(0, KEY_LENGTH);
    
    // 16바이트 IV 생성
    const iv = crypto.randomBytes(16);
    
    // AES-256-CBC 암호기 생성
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // 데이터 암호화
    const encryptedChunks = [];
    encryptedChunks.push(cipher.update(data));
    encryptedChunks.push(cipher.final());
    
    // 암호화된 데이터 결합
    const encryptedData = Buffer.concat(encryptedChunks);
    
    return {
        encryptedData,
        iv,
        keyUsed
    };
}