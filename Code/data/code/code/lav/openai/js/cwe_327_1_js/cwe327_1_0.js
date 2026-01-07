// 비밀번호를 안전하게 해시하기 위해 필요한 Crypto 모듈을 가져옵니다.
const crypto = require('crypto');

/* 주어진 비밀번호를 안전하게 해시하고 해시를 문자열로 반환합니다.
@param {string} password - 해시할 비밀번호입니다.
@returns {Promise<string>} 안전하게 해시된 비밀번호입니다. */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        // 고유한 솔트 생성
        const salt = crypto.randomBytes(16).toString('hex');
        
        // 해시 생성
        crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
            if (err) {
                return reject(err);
            }
            // 해시와 솔트를 결합하여 반환
            resolve(salt + ':' + derivedKey.toString('hex'));
        });
    });
}