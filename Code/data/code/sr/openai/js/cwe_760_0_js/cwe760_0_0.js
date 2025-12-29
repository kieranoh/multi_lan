const crypto = require('crypto');

/**
 * Hashes user passwords using pbkdf2Sync with SHA-256, salt of the same length as the output hash, and 10000 iterations.
 * Returns the hashed passwords and salts used for hashing for further storage in the database.
 *
 * @param {string[]} usernames - Array of usernames.
 * @param {string[]} passwords - Array of user passwords to be hashed.
 * @return {Array<[Buffer, Buffer]>} Array of pairs containing the hashed passwords and salts used for hashing.
 */
function hashPasswords(usernames, passwords) {
    const hashedPasswordsWithSalts = [];

    for (let i = 0; i < passwords.length; i++) {
        const salt = crypto.randomBytes(32); // Generate a random salt of 32 bytes
        const hash = crypto.pbkdf2Sync(passwords[i], salt, 10000, 32, 'sha256'); // Hash the password

        hashedPasswordsWithSalts.push([hash, salt]); // Store the hash and salt as a pair
    }

    return hashedPasswordsWithSalts;
}