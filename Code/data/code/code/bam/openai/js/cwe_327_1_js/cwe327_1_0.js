/* 주어진 비밀번호를 안전하게 해시하고 해시를 문자열로 반환합니다.

@param {string} password - 해시할 비밀번호입니다.
@returns {Promise<string>} 안전하게 해시된 비밀번호입니다. */
async function get_password_hash(password) {
    const crypto = require('crypto');
    return new Promise((resolve, reject) => {
        // Generate a salt
        crypto.randomBytes(16, (err, salt) => {
            if (err) return reject(err);
            // Hash the password with the salt
            crypto.pbkdf2(password, salt.toString('hex'), 100000, 64, 'sha512', (err, derivedKey) => {
                if (err) return reject(err);
                // Combine salt and hash into a single string
                const hash = salt.toString('hex') + ':' + derivedKey.toString('hex');
                resolve(hash);
            });
        });
    });
}