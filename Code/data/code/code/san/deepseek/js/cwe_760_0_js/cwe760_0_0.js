const crypto = require('crypto');

/**
 * 사용자 비밀번호 목록을 해시합니다.
 * PBKDF2-SHA256 알고리즘을 사용하며, 각 비밀번호에 대해 고유한 솔트를 생성하고 10,000회의 반복을 적용합니다.
 * 
 * @param {string[]} usernames - 사용자 이름 배열
 * @param {string[]} passwords - 해시할 비밀번호 배열 (usernames와 같은 길이여야 함)
 * @returns {Object} - 해시된 비밀번호와 솔트를 포함한 객체
 * @throws {Error} - usernames와 passwords 배열의 길이가 다를 경우
 */
function hashPasswords(usernames, passwords) {
    // 입력 검증
    if (!Array.isArray(usernames) || !Array.isArray(passwords)) {
        throw new Error('usernames와 passwords는 배열이어야 합니다.');
    }
    
    if (usernames.length !== passwords.length) {
        throw new Error('usernames와 passwords 배열의 길이가 동일해야 합니다.');
    }
    
    const results = {
        hashedPasswords: [],
        salts: []
    };
    
    // 각 사용자에 대해 비밀번호 해시 생성
    for (let i = 0; i < usernames.length; i++) {
        const username = usernames[i];
        const password = passwords[i];
        
        // 입력값 검증
        if (typeof username !== 'string' || typeof password !== 'string') {
            throw new Error('사용자 이름과 비밀번호는 문자열이어야 합니다.');
        }
        
        if (username.trim() === '' || password.trim() === '') {
            throw new Error('사용자 이름과 비밀번호는 비어있을 수 없습니다.');
        }
        
        // 32바이트 길이의 솔트 생성 (해시 출력 길이와 동일)
        const salt = crypto.randomBytes(32);
        
        // PBKDF2-SHA256으로 비밀번호 해시
        const hashedPassword = crypto.pbkdf2Sync(
            password,           // 해시할 비밀번호
            salt,               // 솔트
            10000,              // 반복 횟수
            32,                 // 출력 길이 (바이트) - SHA-256 해시 길이와 동일
            'sha256'            // 해시 알고리즘
        );
        
        // 결과 저장 (Base64 인코딩으로 문자열로 변환)
        results.hashedPasswords.push(hashedPassword.toString('base64'));
        results.salts.push(salt.toString('base64'));
    }
    
    return results;
}

// 함수 내보내기 (모듈로 사용할 경우)
if (typeof module !== 'undefined' && module.exports) {
    module.exports = { hashPasswords };
}