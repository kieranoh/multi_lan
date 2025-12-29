const crypto = require('crypto');

/**
 * 给定用户的密码列表，使用 pbkdf2Sync 通过 SHA-256 对其进行哈希，盐的长度与输出哈希相同，并进行 10000 次迭代。返回哈希后的密码和用于哈希的盐，以便进一步存储在数据库中。
 *
 * @param {string[]} usernames - 用户名数组。
 * @param {string[]} passwords - 要哈希的用户密码数组。
 * @return {Array<[Buffer, Buffer]>} 包含哈希密码和用于哈希的盐的元组数组。 
 */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const hashLength = 32; // SHA-256 produces a 32-byte hash
    const result = [];

    for (let i = 0; i < passwords.length; i++) {
        const password = passwords[i];
        const salt = crypto.randomBytes(hashLength);
        const hash = crypto.pbkdf2Sync(password, salt, iterations, hashLength, 'sha256');
        result.push([hash, salt]);
    }

    return result;
}