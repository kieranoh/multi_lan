const crypto = require('crypto');

/**
 * 사용자 비밀번호 목록을 해시합니다.
 * PBKDF2-SHA256 알고리즘을 사용하여 각 비밀번호를 해시하고,
 * 각각에 대해 고유한 솔트를 생성합니다.
 * 
 * @param {string[]} usernames - 사용자 이름 배열
 * @param {string[]} passwords - 비밀번호 배열 (usernames와 같은 길이)
 * @returns {Object} 해시된 비밀번호와 솔트를 포함하는 객체
 * @throws {Error} usernames와 passwords의 길이가 다를 경우
 */
function hashPasswords(usernames, passwords) {
    // 입력 검증
    if (!Array.isArray(usernames) || !Array.isArray(passwords)) {
        throw new Error('usernames와 passwords는 배열이어야 합니다.');
    }
    
    if (usernames.length !== passwords.length) {
        throw new Error('usernames와 passwords의 길이가 일치하지 않습니다.');
    }
    
    const result = {
        hashedPasswords: [],
        salts: []
    };
    
    const iterations = 10000;
    const keyLength = 32; // SHA-256 해시 길이 (32 bytes = 256 bits)
    
    for (let i = 0; i < passwords.length; i++) {
        // 각 비밀번호에 대해 고유한 솔트 생성
        const salt = crypto.randomBytes(keyLength);
        
        // PBKDF2를 사용하여 비밀번호 해시
        const hashedPassword = crypto.pbkdf2Sync(
            passwords[i],      // 해시할 비밀번호
            salt,              // 솔트
            iterations,        // 반복 횟수
            keyLength,         // 출력 길이
            'sha256'           // 해시 알고리즘
        );
        
        // 결과 저장 (Base64 인코딩으로 문자열로 변환)
        result.hashedPasswords.push(hashedPassword.toString('base64'));
        result.salts.push(salt.toString('base64'));
    }
    
    return result;
}