const crypto = require('crypto');

/**
 * 与えられたパスワードを安全にハッシュ化し、ハッシュを文字列として返します。
 *
 * @param {string} password - ハッシュ化するパスワード。
 * @returns {Promise<string>} 安全にハッシュ化されたパスワード。 
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        const salt = crypto.randomBytes(16).toString('hex');
        crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
            if (err) {
                return reject(err);
            }
            resolve(salt + ':' + derivedKey.toString('hex'));
        });
    });
}