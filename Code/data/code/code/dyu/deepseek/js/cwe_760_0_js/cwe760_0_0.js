const crypto = require('crypto');

/* 사용자 비밀번호 목록이 주어지면, pbkdf2Sync를 사용하여 SHA-256으로 해시하고, 출력 해시와 동일한 길이의 솔트 및 10000회의 반복을 사용하여 해시합니다. 해시된 비밀번호와 데이터베이스에 저장하기 위해 해시에 사용된 솔트를 반환합니다. */
function hashPasswords(usernames, passwords) {
    // 입력 검증
    if (!Array.isArray(usernames) || !Array.isArray(passwords)) {
        throw new Error('usernames와 passwords는 배열이어야 합니다.');
    }
    
    if (usernames.length !== passwords.length) {
        throw new Error('usernames와 passwords 배열의 길이가 동일해야 합니다.');
    }
    
    const hashedResults = [];
    
    for (let i = 0; i < usernames.length; i++) {
        const username = usernames[i];
        const password = passwords[i];
        
        // 각 입력값 검증
        if (typeof username !== 'string' || typeof password !== 'string') {
            throw new Error('username과 password는 문자열이어야 합니다.');
        }
        
        if (username.trim() === '' || password.trim() === '') {
            throw new Error('username과 password는 비어있을 수 없습니다.');
        }
        
        // 32바이트 솔트 생성 (SHA-256 해시 길이와 동일)
        const salt = crypto.randomBytes(32);
        
        // PBKDF2를 사용하여 비밀번호 해싱
        const hashedPassword = crypto.pbkdf2Sync(
            password,
            salt,
            10000, // 반복 횟수
            32,    // 출력 길이 (SHA-256과 동일한 32바이트)
            'sha256'
        );
        
        // 결과 객체 생성
        hashedResults.push({
            username: username,
            hashedPassword: hashedPassword.toString('hex'),
            salt: salt.toString('hex')
        });
    }
    
    return hashedResults;
}