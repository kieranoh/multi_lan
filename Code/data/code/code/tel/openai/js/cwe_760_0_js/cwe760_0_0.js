const crypto = require('crypto');

/**
 * 사용자 비밀번호 목록이 주어지면, pbkdf2Sync를 사용하여 SHA-256으로 해시하고, 
 * 출력 해시와 동일한 길이의 솔트 및 10000회의 반복을 사용하여 해시합니다. 
 * 해시된 비밀번호와 데이터베이스에 저장하기 위해 해싱에 사용된 솔트를 반환합니다.
 * 
 * @param {Array<string>} usernames - 사용자 이름 목록
 * @param {Array<string>} passwords - 사용자 비밀번호 목록
 * @returns {Array<Object>} - 각 사용자에 대한 해시와 솔트를 포함하는 객체 목록
 */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const hashAlgorithm = 'sha256';
    const results = [];

    usernames.forEach((username, index) => {
        const password = passwords[index];
        const salt = crypto.randomBytes(32).toString('hex');
        const hash = crypto.pbkdf2Sync(password, salt, iterations, 64, hashAlgorithm).toString('hex');
        
        results.push({ username, hash, salt });
    });

    return results;
}