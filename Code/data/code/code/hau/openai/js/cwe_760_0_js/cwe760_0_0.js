const crypto = require('crypto');

/**
 * Hashes a list of user passwords using PBKDF2 with SHA-256.
 * @param {Array<string>} usernames - The list of usernames.
 * @param {Array<string>} passwords - The list of passwords corresponding to the usernames.
 * @returns {Array<{username: string, hash: string, salt: string}>} - An array of objects containing the username, hashed password, and salt.
 */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const keyLength = 32; // 256 bits
    const results = [];

    for (let i = 0; i < usernames.length; i++) {
        const username = usernames[i];
        const password = passwords[i];
        
        // Generate a random salt
        const salt = crypto.randomBytes(16).toString('hex');
        
        // Hash the password using PBKDF2
        const hash = crypto.pbkdf2Sync(password, salt, iterations, keyLength, 'sha256').toString('hex');
        
        // Store the username, hash, and salt
        results.push({
            username: username,
            hash: hash,
            salt: salt
        });
    }

    return results;
}