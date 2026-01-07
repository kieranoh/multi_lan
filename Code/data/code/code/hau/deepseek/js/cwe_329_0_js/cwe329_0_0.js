const crypto = require('crypto');

function encrypt_data(key, data) {
    // 키 길이 검증 (AES-256-CBC를 위해 32바이트 필요)
    if (key.length < 64) {
        throw new Error('키는 최소 64바이트 이상이어야 합니다.');
    }
    
    // AES-256-CBC를 위해 키의 처음 32바이트 사용
    const keyUsed = key.slice(0, 32);
    
    // 16바이트 IV 생성
    const iv = crypto.randomBytes(16);
    
    // AES-256-CBC 암호화 생성
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // 데이터 암호화
    let encryptedData = cipher.update(data);
    encryptedData = Buffer.concat([encryptedData, cipher.final()]);
    
    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}