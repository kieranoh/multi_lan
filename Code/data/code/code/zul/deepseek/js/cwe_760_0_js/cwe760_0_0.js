const crypto = require('crypto');

/**
 * 사용자 비밀번호 목록을 PBKDF2-SHA256으로 해시하고, 해시된 비밀번호와 솔트를 반환합니다.
 * 
 * @param {Array<string>} usernames - 사용자 이름 배열
 * @param {Array<string>} passwords - 비밀번호 배열 (usernames와 동일한 길이)
 * @returns {Array<Object>} 각 사용자에 대한 해시 결과 객체 배열
 * @throws {Error} usernames와 passwords 배열 길이가 다를 경우
 */
function hashPasswords(usernames, passwords) {
    // 입력 검증
    if (!Array.isArray(usernames) || !Array.isArray(passwords)) {
        throw new Error('usernames와 passwords는 배열이어야 합니다.');
    }
    
    if (usernames.length !== passwords.length) {
        throw new Error('usernames와 passwords 배열의 길이가 일치해야 합니다.');
    }
    
    const results = [];
    
    for (let i = 0; i < usernames.length; i++) {
        const username = usernames[i];
        const password = passwords[i];
        
        // 입력값 검증
        if (typeof username !== 'string' || username.trim() === '') {
            throw new Error(`인덱스 ${i}: 유효한 사용자 이름이 필요합니다.`);
        }
        
        if (typeof password !== 'string' || password.trim() === '') {
            throw new Error(`인덱스 ${i}: 유효한 비밀번호가 필요합니다.`);
        }
        
        // 32바이트 솔트 생성 (해시 출력 길이와 동일)
        const salt = crypto.randomBytes(32);
        
        // PBKDF2-SHA256으로 해시 (10000회 반복, 32바이트 출력)
        const hashedPassword = crypto.pbkdf2Sync(
            password,
            salt,
            10000, // 반복 횟수
            32,    // 출력 길이 (바이트)
            'sha256'
        );
        
        // 결과 객체 생성
        results.push({
            username: username,
            hashedPassword: hashedPassword.toString('hex'), // 16진수 문자열로 변환
            salt: salt.toString('hex') // 16진수 문자열로 변환
        });
    }
    
    return results;
}