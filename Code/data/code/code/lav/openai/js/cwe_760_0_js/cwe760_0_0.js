const crypto = require('crypto');

/* 사용자 비밀번호 목록이 주어지면, pbkdf2Sync를 사용하여 SHA-256으로 해시하고, 출력 해시와 동일한 길이의 솔트 및 10000회의 반복을 사용하여 해시합니다. 해시된 비밀번호와 데이터베이스에 저장하기 위해 해싱에 사용된 솔트를 반환합니다. */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const hashAlgorithm = 'sha256';
    const hashedPasswords = {};

    for (let i = 0; i < usernames.length; i++) {
        const username = usernames[i];
        const password = passwords[i];

        // Generate a salt
        const salt = crypto.randomBytes(32).toString('hex');

        // Hash the password using pbkdf2Sync
        const hash = crypto.pbkdf2Sync(password, salt, iterations, 32, hashAlgorithm).toString('hex');

        // Store the hash along with the salt
        hashedPasswords[username] = { hash, salt };
    }

    return hashedPasswords;
}