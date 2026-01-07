const crypto = require('crypto');

/**
 * 사용자 비밀번호 목록을 해시하고 솔트를 생성합니다.
 * 
 * @param {string[]} usernames - 사용자 이름 배열
 * @param {string[]} passwords - 평문 비밀번호 배열
 * @returns {Object} 해시된 비밀번호와 솔트를 포함한 객체
 * @throws {Error} 입력 배열의 길이가 다르거나 유효하지 않은 경우
 */
function hashPasswords(usernames, passwords) {
    // 입력 유효성 검사
    if (!Array.isArray(usernames) || !Array.isArray(passwords)) {
        throw new Error('usernames와 passwords는 배열이어야 합니다.');
    }
    
    if (usernames.length !== passwords.length) {
        throw new Error('usernames와 passwords 배열의 길이가 동일해야 합니다.');
    }
    
    if (usernames.length === 0) {
        return { hashedPasswords: [], salts: [] };
    }
    
    const hashedPasswords = [];
    const salts = [];
    
    // 각 사용자에 대해 비밀번호 해시 생성
    for (let i = 0; i < usernames.length; i++) {
        const username = usernames[i];
        const password = passwords[i];
        
        // 입력값 유효성 검사
        if (typeof username !== 'string' || typeof password !== 'string') {
            throw new Error('사용자 이름과 비밀번호는 문자열이어야 합니다.');
        }
        
        if (username.trim() === '' || password.trim() === '') {
            throw new Error('사용자 이름과 비밀번호는 비어있을 수 없습니다.');
        }
        
        // 32바이트 길이의 솔트 생성 (SHA-256 해시 길이와 동일)
        const salt = crypto.randomBytes(32).toString('hex');
        
        // PBKDF2를 사용하여 비밀번호 해시 생성
        const hashedPassword = crypto.pbkdf2Sync(
            password,           // 평문 비밀번호
            salt,               // 솔트
            10000,              // 반복 횟수
            32,                 // 키 길이 (32바이트 = 256비트)
            'sha256'            // 해시 알고리즘
        ).toString('hex');      // 16진수 문자열로 변환
        
        hashedPasswords.push(hashedPassword);
        salts.push(salt);
    }
    
    return {
        hashedPasswords: hashedPasswords,
        salts: salts
    };
}