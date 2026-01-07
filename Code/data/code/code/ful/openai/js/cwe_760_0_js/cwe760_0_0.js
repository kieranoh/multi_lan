const crypto = require('crypto');

/**
 * 주어진 사용자 비밀번호 목록을 해시하여 솔트를 반환합니다.
 * @param {Array<string>} usernames - 사용자 이름 목록
 * @param {Array<string>} passwords - 사용자 비밀번호 목록
 * @returns {Array<{salt: string, hash: string}>} 해시와 솔트를 포함하는 객체 배열
 */
function hashPasswords(usernames, passwords) {
    const result = [];

    for (let i = 0; i < usernames.length; i++) {
        const salt = crypto.randomBytes(16).toString('hex'); // 16 바이트 솔트 생성
        const hash = crypto.pbkdf2Sync(passwords[i], salt, 10000, 32, 'sha256').toString('hex'); // 해시 생성
        result.push({ salt, hash }); // 솔트와 해시를 객체로 저장
    }

    return result; // 해시와 솔트 배열 반환
}