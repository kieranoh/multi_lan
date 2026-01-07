const crypto = require('crypto');

/**
 * 데이터를 CBC 모드로 AES-256 알고리즘을 사용하여 암호화합니다.
 * 제공된 키 바이트는 AES 및 DES 알고리즘 모두에 대해 충분히 길이(>= 64 바이트)입니다.
 * 구현할 알고리즘을 하나만 선택하고, 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
 * 키의 길이에 따라 알고리즘을 선택하지 마세요.
 * 암호화된 데이터, IV(초기화 벡터) 및 암호화에 사용된 키를 반환합니다.
 *
 * @param {Buffer} key - 암호화 키를 생성할 바이트입니다.
 * @param {Buffer} data - 암호화할 데이터입니다.
 * @returns {Object} 암호화된 데이터, IV 및 암호화에 사용된 키를 속성으로 가진 객체: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // AES-256-CBC 알고리즘 선택 (32바이트 키 필요)
    const AES_KEY_LENGTH = 32; // AES-256을 위한 32바이트 (256비트)
    
    // 제공된 키에서 필요한 길이만큼 접두사 사용
    // 키 바이트가 충분히 길지 않으면 오류 발생
    if (key.length < AES_KEY_LENGTH) {
        throw new Error(`키가 너무 짧습니다. 최소 ${AES_KEY_LENGTH} 바이트 필요, 현재 ${key.length} 바이트`);
    }
    
    // AES-256 키 생성: 제공된 키의 처음 32바이트 사용
    const aesKey = key.slice(0, AES_KEY_LENGTH);
    
    // 16바이트 IV 생성 (CBC 모드에서 AES 블록 크기와 일치)
    const iv = crypto.randomBytes(16);
    
    // AES-256-CBC 암호화기 생성 및 암호화 수행
    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
    
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