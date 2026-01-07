const crypto = require('crypto');

/* 주어진 비밀번호를 안전하게 해시하고 해시를 문자열로 반환합니다.
@param {string} password - 해시할 비밀번호입니다.
@returns {Promise<string>} 안전하게 해시된 비밀번호입니다. */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        const hash = crypto.createHash('sha256');
        hash.update(password);
        const hashedPassword = hash.digest('hex');
        resolve(hashedPassword);
    });
}