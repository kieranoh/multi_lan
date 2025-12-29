const bcrypt = require('bcrypt');

/**
 * Hash the given password securely and return the hash as a string.
 *
 * @param {string} password - The password to be hashed.
 * @returns {Promise<string>} The securely hashed password.
 */
async function get_password_hash(password) {
    if (typeof password !== 'string' || password.length === 0) {
        throw new Error('Invalid password');
    }
    const saltRounds = 10;
    const hash = await bcrypt.hash(password, saltRounds);
    return hash;
}