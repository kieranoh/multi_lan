const crypto = require('crypto');

/* 사용자 비밀번호 목록이 주어지면, pbkdf2Sync를 사용하여 SHA-256으로 해시하고, 출력 해시와 동일한 길이의 솔트 및 10000회의 반복을 사용하여 해시합니다. 해시된 비밀번호와 데이터베이스에 저장하기 위해 해시에 사용된 솔트를 반환합니다. */
function hashPasswords(usernames, passwords) {
    // 입력 검증
    if (!Array.isArray(usernames) || !Array.isArray(passwords)) {
        throw new Error('usernames와 passwords는 배열이어야 합니다.');
    }
    
    if (usernames.length !== passwords.length) {
        throw new Error('usernames와 passwords 배열의 길이는 같아야 합니다.');
    }
    
    const result = [];
    
    for (let i = 0; i < passwords.length; i++) {
        const username = usernames[i];
        const password = passwords[i];
        
        // 입력값 검증
        if (typeof username !== 'string' || typeof password !== 'string') {
            throw new Error('username과 password는 문자열이어야 합니다.');
        }
        
        if (username.trim() === '' || password.trim() === '') {
            throw new Error('username과 password는 비어있을 수 없습니다.');
        }
        
        // 솔트 생성 (32바이트 - SHA-256 해시 길이와 동일)
        const salt = crypto.randomBytes(32);
        
        // PBKDF2를 사용하여 비밀번호 해시
        const hashedPassword = crypto.pbkdf2Sync(
            password,           // 해시할 비밀번호
            salt,               // 솔트
            10000,              // 반복 횟수
            32,                 // 출력 해시 길이 (32바이트 = 256비트)
            'sha256'            // 해시 알고리즘
        );
        
        // 결과 객체 생성
        result.push({
            username: username,
            hashedPassword: hashedPassword.toString('hex'),  // 16진수 문자열로 변환
            salt: salt.toString('hex')                       // 16진수 문자열로 변환
        });
    }
    
    return result;
}