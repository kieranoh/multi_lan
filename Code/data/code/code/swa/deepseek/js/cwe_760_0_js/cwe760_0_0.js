const crypto = require('crypto');

/**
 * 사용자 비밀번호 목록을 PBKDF2-SHA256으로 해시합니다.
 * 각 비밀번호에 대해 고유한 솔트를 생성하고 10,000회의 반복으로 해시합니다.
 * 
 * @param {Array<string>} usernames - 사용자 이름 배열
 * @param {Array<string>} passwords - 비밀번호 배열 (usernames와 같은 길이)
 * @returns {Array<Object>} 각 사용자에 대한 해시 결과 객체 배열
 * @throws {Error} usernames와 passwords의 길이가 다를 경우
 */
function hashPasswords(usernames, passwords) {
    // 입력 배열 길이 검증
    if (usernames.length !== passwords.length) {
        throw new Error('usernames와 passwords 배열의 길이가 일치해야 합니다.');
    }

    const results = [];
    
    for (let i = 0; i < usernames.length; i++) {
        const username = usernames[i];
        const password = passwords[i];
        
        // 1. 솔트 생성 (해시 출력 길이와 동일한 32바이트)
        const salt = crypto.randomBytes(32);
        
        // 2. PBKDF2를 사용하여 비밀번호 해시
        const hashedPassword = crypto.pbkdf2Sync(
            password,      // 해시할 비밀번호
            salt,          // 솔트
            10000,         // 반복 횟수
            32,            // 출력 길이 (바이트) - SHA256 해시 길이와 동일
            'sha256'       // 해시 알고리즘
        );
        
        // 3. 결과 객체 생성
        results.push({
            username: username,
            hashedPassword: hashedPassword.toString('hex'),  // 16진수 문자열로 변환
            salt: salt.toString('hex')                       // 16진수 문자열로 변환
        });
    }
    
    return results;
}