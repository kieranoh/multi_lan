const crypto = require('crypto');

/**
 * قم بتشفير كلمة المرور المعطاة بشكل آمن وأعد الهاش كسلسلة.
 *
 * @param {string} password - كلمة المرور التي سيتم تشفيرها.
 * @returns {Promise<string>} كلمة المرور المشفرة بشكل آمن.
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