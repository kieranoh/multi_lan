const crypto = require('crypto');

/**
 * AES 및 CBC 모드를 사용하여 키로 데이터를 암호화합니다.
 * 제공된 키 바이트가 충분히 깁니다 (>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
 * 암호화된 데이터, IV(초기화 벡터) 및 암호화에 사용된 키를 반환합니다.
 *
 * @param {Buffer} key - 암호화 키를 생성할 바이트 (최소 16 바이트).
 * @param {Buffer} data - 암호화할 데이터.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} 암호화된 데이터, IV 및 암호화에 사용된 키.
 */
function encrypt_data(key, data) {
    // 키 길이 검증
    if (!Buffer.isBuffer(key)) {
        throw new TypeError('key must be a Buffer');
    }
    if (!Buffer.isBuffer(data)) {
        throw new TypeError('data must be a Buffer');
    }
    if (key.length < 16) {
        throw new Error('key must be at least 16 bytes');
    }

    // AES-256-CBC를 사용하기 위해 32바이트 키 생성
    // 제공된 키가 충분히 길면(>=64바이트) 접두사 사용, 아니면 필요한 만큼 확장
    const keyLength = 32; // AES-256
    let keyUsed;
    
    if (key.length >= keyLength) {
        // 충분히 길면 접두사 사용
        keyUsed = key.slice(0, keyLength);
    } else {
        // 부족하면 PBKDF2로 확장 (안전한 키 파생)
        const salt = crypto.randomBytes(16);
        keyUsed = crypto.pbkdf2Sync(key, salt, 100000, keyLength, 'sha256');
    }

    // IV 생성 (16바이트)
    const iv = crypto.randomBytes(16);

    // AES-256-CBC 암호화
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // 데이터 암호화
    const encryptedChunks = [];
    encryptedChunks.push(cipher.update(data));
    encryptedChunks.push(cipher.final());
    
    const encryptedData = Buffer.concat(encryptedChunks);

    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}