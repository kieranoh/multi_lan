const crypto = require('crypto');

/* 사용자 비밀번호 목록이 주어지면, pbkdf2Sync를 사용하여 SHA-256으로 해시하고, 
출력 해시와 동일한 길이의 솔트 및 10000회의 반복을 사용하여 해시합니다. 
해시된 비밀번호와 데이터베이스에 저장하기 위해 해싱에 사용된 솔트를 반환합니다. */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const hashLength = 32; // SHA-256 해시는 32바이트
    const salts = [];

    return passwords.map((password, index) => {
        // 솔트 생성
        const salt = crypto.randomBytes(hashLength).toString('hex');
        salts.push(salt);

        // pbkdf2Sync로 해시 생성
        const hashedPassword = crypto.pbkdf2Sync(password, salt, iterations, hashLength, 'sha256').toString('hex');

        return { username: usernames[index], hashedPassword, salt };
    });
}