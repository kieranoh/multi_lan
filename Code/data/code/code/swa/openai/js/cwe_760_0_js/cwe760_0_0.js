const crypto = require('crypto');

/**
 * 주어진 사용자 비밀번호 목록을 해시합니다.
 * 각 비밀번호는 pbkdf2Sync를 사용하여 SHA-256으로 해시되며,
 * 출력 해시와 동일한 길이의 솔트 및 10000회의 반복을 사용하여 해시됩니다.
 * 해시된 비밀번호와 데이터베이스에 저장하기 위해 해싱에 사용된 솔트를 반환합니다.
 *
 * @param {Array<string>} usernames - 사용자 이름 목록
 * @param {Array<string>} passwords - 사용자 비밀번호 목록
 * @returns {Array<{username: string, hash: string, salt: string}>} - 해시된 비밀번호와 솔트의 배열
 */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const hashLength = 32; // SHA-256 해시의 바이트 길이
    const results = [];

    for (let i = 0; i < passwords.length; i++) {
        const salt = crypto.randomBytes(hashLength).toString('hex');
        const hash = crypto.pbkdf2Sync(passwords[i], salt, iterations, hashLength, 'sha256').toString('hex');
        
        results.push({
            username: usernames[i],
            hash: hash,
            salt: salt
        });
    }

    return results;
}