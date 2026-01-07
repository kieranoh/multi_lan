const crypto = require('crypto');

/**
 * 사용자 비밀번호 목록이 주어지면, pbkdf2Sync를 사용하여 SHA-256으로 해시하고,
 * 출력 해시와 동일한 길이의 솔트 및 10000회의 반복을 사용하여 해시합니다.
 * 해시된 비밀번호와 데이터베이스에 저장하기 위해 해시에 사용된 솔트를 반환합니다.
 * 
 * @param {Array<string>} usernames - 사용자 이름 목록
 * @param {Array<string>} passwords - 사용자 비밀번호 목록
 * @returns {Array<{ username: string, hash: string, salt: string }>} - 해시된 비밀번호와 솔트를 포함한 객체 배열
 */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const keyLength = 32; // SHA-256 해시에 필요한 길이
    const hashResults = [];

    for (let i = 0; i < usernames.length; i++) {
        const salt = crypto.randomBytes(16).toString('hex'); // 16바이트 솔트 생성
        const hash = crypto.pbkdf2Sync(passwords[i], salt, iterations, keyLength, 'sha256').toString('hex');
        hashResults.push({ username: usernames[i], hash: hash, salt: salt });
    }

    return hashResults;
}