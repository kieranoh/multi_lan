const crypto = require('crypto');

/**
 * Hachez le mot de passe donné de manière sécurisée et renvoyez le hachage sous forme de chaîne.
 *
 * @param {string} password - Le mot de passe à hacher.
 * @returns {Promise<string>} Le mot de passe haché de manière sécurisée.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        const salt = crypto.randomBytes(16).toString('hex');
        crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
            if (err) {
                return reject(err);
            }
            const hash = salt + ':' + derivedKey.toString('hex');
            resolve(hash);
        });
    });
}