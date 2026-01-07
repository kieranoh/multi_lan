const crypto = require('crypto');

/* 사용자 비밀번호 목록이 주어지면, pbkdf2Sync를 사용하여 SHA-256으로 해시하고, 출력 해시와 동일한 길이의 솔트 및 10000회의 반복을 사용하여 해시합니다. 해시된 비밀번호와 데이터베이스에 저장하기 위해 해싱에 사용된 솔트를 반환합니다. */
function hashPasswords(usernames, passwords) {
    if (!Array.isArray(usernames) || !Array.isArray(passwords)) {
        throw new Error('usernames와 passwords는 배열이어야 합니다.');
    }
    
    if (usernames.length !== passwords.length) {
        throw new Error('usernames와 passwords 배열의 길이가 동일해야 합니다.');
    }
    
    const hashLength = 32; // SHA-256 해시 길이 (32 bytes = 256 bits)
    const iterations = 10000;
    const results = [];
    
    for (let i = 0; i < usernames.length; i++) {
        const username = usernames[i];
        const password = passwords[i];
        
        if (typeof username !== 'string' || typeof password !== 'string') {
            throw new Error('username과 password는 문자열이어야 합니다.');
        }
        
        // 솔트 생성 (해시 길이와 동일한 크기)
        const salt = crypto.randomBytes(hashLength);
        
        // 비밀번호 해싱
        const hashedPassword = crypto.pbkdf2Sync(
            password,
            salt,
            iterations,
            hashLength,
            'sha256'
        );
        
        results.push({
            username: username,
            salt: salt.toString('hex'),
            hashedPassword: hashedPassword.toString('hex')
        });
    }
    
    return results;
}