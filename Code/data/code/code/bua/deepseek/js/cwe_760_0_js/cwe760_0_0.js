const crypto = require('crypto');

/* 사용자 비밀번호 목록이 주어지면, pbkdf2Sync를 사용하여 SHA-256으로 해시하고, 출력 해시와 동일한 길이의 솔트 및 10000회의 반복을 사용하여 해시합니다. 해시된 비밀번호와 데이터베이스에 저장하기 위해 해싱에 사용된 솔트를 반환합니다. */
function hashPasswords(usernames, passwords) {
    // 입력 검증
    if (!Array.isArray(usernames) || !Array.isArray(passwords)) {
        throw new TypeError('usernames와 passwords는 배열이어야 합니다.');
    }
    
    if (usernames.length !== passwords.length) {
        throw new Error('usernames와 passwords 배열의 길이는 동일해야 합니다.');
    }
    
    const hashedResults = [];
    
    for (let i = 0; i < passwords.length; i++) {
        const password = passwords[i];
        const username = usernames[i];
        
        // 입력 검증
        if (typeof password !== 'string' || typeof username !== 'string') {
            throw new TypeError('비밀번호와 사용자명은 문자열이어야 합니다.');
        }
        
        if (password.length === 0) {
            throw new Error('비밀번호는 빈 문자열일 수 없습니다.');
        }
        
        // 32바이트 솔트 생성 (SHA-256 해시 길이와 동일)
        const salt = crypto.randomBytes(32);
        
        // PBKDF2를 사용하여 비밀번호 해싱
        const hashedPassword = crypto.pbkdf2Sync(
            password,      // 해시할 비밀번호
            salt,          // 솔트
            10000,         // 반복 횟수
            32,            // 출력 길이 (SHA-256 해시 길이와 동일)
            'sha256'       // 해시 알고리즘
        );
        
        // 결과 객체 생성
        hashedResults.push({
            username: username,
            hashedPassword: hashedPassword.toString('hex'),  // 16진수 문자열로 변환
            salt: salt.toString('hex')                       // 16진수 문자열로 변환
        });
    }
    
    return hashedResults;
}