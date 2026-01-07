const crypto = require('crypto');

/**
 * 사용자 비밀번호 목록을 해시합니다.
 * PBKDF2-SHA256 알고리즘을 사용하여 각 비밀번호를 해시하고,
 * 각 해시에 대해 고유한 솔트를 생성합니다.
 * 
 * @param {Array<string>} usernames - 사용자 이름 배열
 * @param {Array<string>} passwords - 해시할 비밀번호 배열
 * @returns {Object} 해시된 비밀번호와 솔트를 포함하는 객체
 * @property {Array<string>} hashedPasswords - 해시된 비밀번호 배열 (16진수 문자열)
 * @property {Array<string>} salts - 각 비밀번호에 사용된 솔트 배열 (16진수 문자열)
 * 
 * @throws {Error} usernames와 passwords 배열의 길이가 다를 경우
 */
function hashPasswords(usernames, passwords) {
    // 입력 배열 길이 검증
    if (usernames.length !== passwords.length) {
        throw new Error('usernames와 passwords 배열의 길이가 일치해야 합니다.');
    }

    const hashedPasswords = [];
    const salts = [];
    const iterations = 10000;
    const keyLength = 32; // SHA-256 해시 길이 (32 bytes = 256 bits)

    for (let i = 0; i < passwords.length; i++) {
        // 각 비밀번호에 대해 고유한 솔트 생성
        const salt = crypto.randomBytes(keyLength);
        
        // PBKDF2를 사용하여 비밀번호 해시
        const hashedPassword = crypto.pbkdf2Sync(
            passwords[i],
            salt,
            iterations,
            keyLength,
            'sha256'
        );
        
        // 결과를 16진수 문자열로 변환하여 저장
        salts.push(salt.toString('hex'));
        hashedPasswords.push(hashedPassword.toString('hex'));
    }

    return {
        hashedPasswords: hashedPasswords,
        salts: salts
    };
}