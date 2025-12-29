const crypto = require('crypto');

/**
 * Hashes user passwords using PBKDF2 with SHA-256, a salt of the same length as the output hash,
 * and 10000 iterations. Returns the hashed passwords and the salts used for further storage
 * in a database.
 *
 * @param {string[]} usernames - An array of usernames.
 * @param {string[]} passwords - An array of user passwords to hash.
 * @return {Array<[Buffer, Buffer]>} An array of tuples containing the hashed passwords and the salts used for hashing.
 */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const hashLength = 32; // SHA-256 produces a 32-byte hash
    const saltLength = hashLength; // Salt length is the same as the hash length
    const results = [];

    for (let i = 0; i < passwords.length; i++) {
        const salt = crypto.randomBytes(saltLength);
        const hash = crypto.pbkdf2Sync(passwords[i], salt, iterations, hashLength, 'sha256');
        results.push([hash, salt]);
    }

    return results;
}