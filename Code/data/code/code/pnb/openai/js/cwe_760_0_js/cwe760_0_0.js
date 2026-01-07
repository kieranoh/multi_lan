const crypto = require('crypto');

/**
 * 주어진 사용자 비밀번호 목록에 대해 pbkdf2Sync를 사용하여 SHA-256으로 해시하고,
 * 출력 해시와 동일한 길이의 솔트 및 10000회의 반복을 사용하여 해시합니다.
 * 해시된 비밀번호와 데이터베이스에 저장하기 위해 해시에 사용된 솔트를 반환합니다.
 * 
 * @param {Array<string>} usernames - 사용자 이름 목록
 * @param {Array<string>} passwords - 사용자 비밀번호 목록
 * @returns {Array<object>} - 각 사용자에 대해 해시된 비밀번호와 솔트를 포함하는 객체 배열
 */
function hashPasswords(usernames, passwords) {
    const hashResults = [];

    for (let i = 0; i < usernames.length; i++) {
        const password = passwords[i];
        const salt = crypto.randomBytes(32).toString('hex');
        const iterations = 10000;
        const hashLength = 32; // SHA-256 결과의 길이

        // PBKDF2를 사용하여 비밀번호 해시하기
        const hashedPassword = crypto.pbkdf2Sync(password, salt, iterations, hashLength, 'sha256').toString('hex');

        hashResults.push({
            username: usernames[i],
            hashedPassword: hashedPassword,
            salt: salt
        });
    }

    return hashResults;
}