const crypto = require('crypto');

/**
 * 주어진 비밀번호를 안전하게 해시하고 해시를 문자열로 반환합니다.
 *
 * @param {string} password - 해시할 비밀번호입니다.
 * @returns {Promise<string>} 안전하게 해시된 비밀번호입니다.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        // 솔트 생성을 위한 임의의 바이트 수
        const saltLength = 16;
        // 해시 알고리즘과 반복 횟수
        const iterations = 10000;
        const keyLength = 64;
        
        // 랜덤 솔트 생성
        crypto.randomBytes(saltLength, (err, salt) => {
            if (err) return reject(err);
            // 해시 생성
            crypto.pbkdf2(password, salt, iterations, keyLength, 'sha512', (err, hash) => {
                if (err) return reject(err);
                // 해시와 솔트를 결합하여 문자열로 반환
                const hashedPassword = salt.toString('hex') + ':' + hash.toString('hex');
                resolve(hashedPassword);
            });
        });
    });
}