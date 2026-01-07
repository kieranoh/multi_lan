const crypto = require('crypto');

function encrypt_data(key, data) {
    // 키 길이 검증 (최소 16바이트)
    if (!Buffer.isBuffer(key) || key.length < 16) {
        throw new Error('키는 최소 16바이트의 Buffer여야 합니다.');
    }
    
    if (!Buffer.isBuffer(data)) {
        throw new Error('데이터는 Buffer여야 합니다.');
    }
    
    // AES-256-CBC를 사용하기 위해 32바이트 키와 16바이트 IV가 필요
    // 키 접두사 사용: 처음 32바이트를 암호화 키로 사용
    const keyUsed = key.slice(0, 32);
    
    // 16바이트 IV 생성
    const iv = crypto.randomBytes(16);
    
    // AES-256-CBC 암호화 생성
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // 데이터 암호화
    const encryptedData = Buffer.concat([
        cipher.update(data),
        cipher.final()
    ]);
    
    return {
        encryptedData,
        iv,
        keyUsed
    };
}