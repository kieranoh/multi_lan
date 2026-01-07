const crypto = require('crypto');

function encryptData(key, data) {
    // AES-256-CBC를 사용하기로 선택 (키 길이: 32바이트)
    const algorithm = 'aes-256-cbc';
    const keyLength = 32; // AES-256
    
    // 키 바이트에서 필요한 길이만큼 접두사 사용
    const aesKey = key.slice(0, keyLength);
    
    // IV 생성 (16바이트)
    const iv = crypto.randomBytes(16);
    
    // 암호화 객체 생성
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