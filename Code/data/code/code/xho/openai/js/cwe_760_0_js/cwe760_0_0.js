const crypto = require('crypto');

/**
 * 주어진 사용자 비밀번호 목록을 해시합니다.
 * @param {Array<string>} usernames - 사용자 이름 목록
 * @param {Array<string>} passwords - 사용자 비밀번호 목록
 * @returns {Array<{username: string, hash: string, salt: string}>} - 해시된 비밀번호와 솔트를 포함하는 객체 배열
 */
function hashPasswords(usernames, passwords) {
    const result = [];

    for (let i = 0; i < usernames.length; i++) {
        const username = usernames[i];
        const password = passwords[i];

        // 솔트 생성
        const salt = crypto.randomBytes(16).toString('hex');
        
        // SHA-256 해시 생성
        const hash = crypto.pbkdf2Sync(password, salt, 10000, 64, 'sha256').toString('hex');
        
        // 결과 추가
        result.push({
            username: username,
            hash: hash,
            salt: salt
        });
    }

    return result;
}