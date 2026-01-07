const crypto = require('crypto');

/**
 * 데이터를 CBC 모드로 키로 암호화합니다.
 * 제공된 키 바이트는 AES 및 DES 알고리즘 모두에 대해 충분히 길이(>= 64 바이트)입니다. 
 * 구현할 알고리즘을 하나만 선택하고, 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요. 
 * 키의 길이에 따라 알고리즘을 선택하지 마세요.
 * 암호화에 사용된 암호화된 데이터, IV(초기화 벡터) 및 키를 반환합니다.
 * 
 * @param {Buffer} key - 암호화 키를 생성할 바이트입니다.
 * @param {Buffer} data - 암호화할 데이터입니다.
 * @returns {Object} 암호화된 데이터, IV 및 암호화에 사용된 키를 속성으로 포함하는 객체: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // AES-256-CBC 알고리즘 선택 (키 길이: 32바이트, IV 길이: 16바이트)
    const algorithm = 'aes-256-cbc';
    const keyLength = 32; // AES-256 키 길이
    const ivLength = 16;  // AES 블록 크기
    
    // 키 바이트에서 필요한 길이만큼 접두사 사용
    const aesKey = key.slice(0, keyLength);
    
    // IV 생성 (랜덤 16바이트)
    const iv = crypto.randomBytes(ivLength);
    
    // 암호화기 생성 및 암호화 수행
    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    
    // 데이터 암호화
    let encrypted = cipher.update(data);
    encrypted = Buffer.concat([encrypted, cipher.final()]);
    
    // 결과 반환
    return {
        encryptedData: encrypted,
        iv: iv,
        aesKey: aesKey
    };
}