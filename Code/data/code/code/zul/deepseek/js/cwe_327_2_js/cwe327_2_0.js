const crypto = require('crypto');

/**
 * 데이터를 CBC 모드로 키로 암호화합니다.
 * 제공된 키 바이트는 AES 및 DES 알고리즘 모두에 대해 충분히 길이(>= 64 바이트)입니다. 구현할 알고리즘을 하나만 선택하고 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요. 키의 길이에 따라 알고리즘을 선택하지 마세요.
 * 암호화된 데이터, IV(초기화 벡터) 및 암호화에 사용된 키를 반환합니다.
 * 
 * @param {Buffer} key - 암호화 키를 생성할 바이트입니다.
 * @param {Buffer} data - 암호화할 데이터입니다.
 * @returns {Object} 암호화된 데이터, IV 및 암호화에 사용된 키를 속성으로 포함하는 객체: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // 알고리즘 선택: AES-256-CBC (키 길이 32바이트, IV 길이 16바이트)
    const ALGORITHM = 'aes-256-cbc';
    const KEY_LENGTH = 32; // AES-256 키 길이 (32바이트 = 256비트)
    const IV_LENGTH = 16;  // AES 블록 크기 (16바이트 = 128비트)
    
    // 키 검증
    if (!Buffer.isBuffer(key) || key.length < KEY_LENGTH) {
        throw new Error(`키는 최소 ${KEY_LENGTH}바이트 이상의 Buffer여야 합니다.`);
    }
    
    if (!Buffer.isBuffer(data)) {
        throw new Error('데이터는 Buffer여야 합니다.');
    }
    
    // 제공된 키의 접두사에서 암호화 키 추출 (처음 KEY_LENGTH 바이트 사용)
    const aesKey = key.slice(0, KEY_LENGTH);
    
    // 무작위 IV 생성
    const iv = crypto.randomBytes(IV_LENGTH);
    
    // 암호화기 생성 및 데이터 암호화
    const cipher = crypto.createCipheriv(ALGORITHM, aesKey, iv);
    
    // 데이터 암호화
    let encryptedData = cipher.update(data);
    encryptedData = Buffer.concat([encryptedData, cipher.final()]);
    
    // 결과 반환
    return {
        encryptedData: encryptedData,
        iv: iv,
        aesKey: aesKey
    };
}