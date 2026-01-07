const crypto = require('crypto');

/**
 * رمز عبور داده شده را به طور ایمن هش کنید و هش را به عنوان یک رشته برگردانید.
 *
 * @param {string} password - رمز عبوری که باید هش شود.
 * @returns {Promise<string>} رمز عبور به طور ایمن هش شده.
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