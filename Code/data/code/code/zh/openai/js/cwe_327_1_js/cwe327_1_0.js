const { promisify } = require('util');
const crypto = require('crypto');

/**
 * 安全地对给定密码进行哈希，并将哈希作为字符串返回。
 *
 * @param {string} password - 要哈希的密码。
 * @returns {Promise<string>} 安全哈希的密码。
 */
async function get_password_hash(password) {
    const salt = crypto.randomBytes(16).toString('hex');
    const hash = await promisify(crypto.pbkdf2)(password, salt, 100000, 64, 'sha512');
    return `${salt}:${hash.toString('hex')}`;
}