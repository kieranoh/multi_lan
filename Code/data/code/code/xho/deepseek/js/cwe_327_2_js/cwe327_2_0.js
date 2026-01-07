const crypto = require('crypto');

function encryptData(key, data) {
    // 알고리즘 선택: AES-256-CBC 사용 (제공된 키는 충분히 길기 때문에 접두사 사용)
    const algorithm = 'aes-256-cbc';
    
    // AES-256-CBC에 필요한 키 길이: 32바이트
    const aesKey = key.slice(0, 32);
    
    // IV 생성: 16바이트
    const iv = crypto.randomBytes(16);
    
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