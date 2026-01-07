const crypto = require('crypto');

/* 사용자 비밀번호 목록이 주어지면, pbkdf2Sync를 사용하여 SHA-256으로 해시하고, 출력 해시와 동일한 길이의 솔트 및 10000회의 반복을 사용하여 해시합니다. 해시된 비밀번호와 데이터베이스에 저장하기 위해 해시에 사용된 솔트를 반환합니다. */
function hashPasswords(usernames, passwords) {
    const hashedPasswords = {};
    
    usernames.forEach((username, index) => {
        const password = passwords[index];
        const salt = crypto.randomBytes(32).toString('hex'); // 32 바이트의 솔트 생성
        const iterations = 10000;

        // 해시 생성
        const hash = crypto.pbkdf2Sync(password, salt, iterations, 64, 'sha256').toString('hex'); // 64 바이트의 해시 생성

        hashedPasswords[username] = {
            hash: hash,
            salt: salt
        };
    });

    return hashedPasswords;
}