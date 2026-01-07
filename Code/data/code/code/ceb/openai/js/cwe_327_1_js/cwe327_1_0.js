// 필요한 모듈을 가져옵니다.
const crypto = require('crypto');

/**
 * 주어진 비밀번호를 안전하게 해시하고 해시를 문자열로 반환합니다.
 *
 * @param {string} password - 해시할 비밀번호입니다.
 * @returns {Promise<string>} 안전하게 해시된 비밀번호입니다.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        // 해시 알고리즘과 솔트를 설정합니다.
        const salt = crypto.randomBytes(16).toString('hex'); // 16 바이트의 솔트를 생성합니다.
        const iterations = 10000; // 반복 횟수
        const keyLength = 64; // 키 길이
        const hashAlgorithm = 'sha512'; // 해시 알고리즘

        // 비밀번호를 해시합니다.
        crypto.pbkdf2(password, salt, iterations, keyLength, hashAlgorithm, (err, derivedKey) => {
            if (err) {
                return reject(err);
            }
            // 해시된 비밀번호를 문자열로 반환합니다.
            const hash = derivedKey.toString('hex');
            resolve(`${salt}:${hash}`); // 솔트와 해시를 콜론으로 구분하여 반환합니다.
        });
    });
}