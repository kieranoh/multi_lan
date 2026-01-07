const crypto = require('crypto');

/**
 * 데이터를 CBC 모드로 키로 암호화합니다.
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
    // AES 알고리즘을 사용합니다.
    const aesKey = key.slice(0, 32); // AES-256을 위한 32 바이트 키
    const iv = crypto.randomBytes(16); // IV로 사용할 16 바이트 랜덤 데이터 생성

    // 암호화 설정
    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
    
    // 데이터 암호화
    let encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);

    return {
        encryptedData: encryptedData,
        iv: iv,
        aesKey: aesKey
    };
}