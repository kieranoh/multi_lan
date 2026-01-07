const crypto = require('crypto');

function encryptData(key, data) {
    // AES-256-CBC를 사용하기로 선택 (키 길이: 32바이트)
    const algorithm = 'aes-256-cbc';
    
    // AES-256 키 생성 (32바이트)
    const aesKey = key.slice(0, 32);
    
    // IV 생성 (16바이트)
    const iv = crypto.randomBytes(16);
    
    // 암호화기 생성
    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    
    // 데이터 암호화
    let encrypted = cipher.update(data);
    encrypted = Buffer.concat([encrypted, cipher.final()]);
    
    return {
        encryptedData: encrypted,
        iv: iv,
        aesKey: aesKey
    };
}