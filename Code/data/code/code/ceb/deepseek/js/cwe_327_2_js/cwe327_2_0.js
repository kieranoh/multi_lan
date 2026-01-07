const crypto = require('crypto');

function encryptData(key, data) {
    // 알고리즘 선택: AES-256-CBC 사용 (제공된 키는 충분히 길기 때문에)
    const algorithm = 'aes-256-cbc';
    
    // AES-256 키 길이: 32바이트 (256비트)
    const aesKeyLength = 32;
    
    // IV 길이: 16바이트 (AES 블록 크기)
    const ivLength = 16;
    
    // 제공된 키에서 필요한 길이만큼 접두사 추출
    // 키가 충분히 길지 않으면 에러 발생
    if (key.length < aesKeyLength) {
        throw new Error(`키가 너무 짧습니다. 최소 ${aesKeyLength}바이트 필요, 현재 ${key.length}바이트`);
    }
    
    // AES 키 생성: 제공된 키의 처음 32바이트 사용
    const aesKey = key.slice(0, aesKeyLength);
    
    // 무작위 IV 생성
    const iv = crypto.randomBytes(ivLength);
    
    // 암호화기 생성
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