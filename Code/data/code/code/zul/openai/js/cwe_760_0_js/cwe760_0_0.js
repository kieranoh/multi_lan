const crypto = require('crypto');

/**
 * Hashes a list of user passwords using pbkdf2Sync with SHA-256.
 * It generates a random salt for each password and hashes the password 
 * with the salt for 10,000 iterations. The function returns an array of 
 * objects containing the hashed password and the corresponding salt.
 * 
 * @param {Array<string>} usernames - A list of usernames.
 * @param {Array<string>} passwords - A list of passwords corresponding to the usernames.
 * @returns {Array<object>} - An array of objects with hashed passwords and their salts.
 */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const keyLength = 64; // SHA-256 outputs 32 bytes, but we can take more for security
    const digest = 'sha256';
    
    return usernames.map((username, index) => {
        const password = passwords[index];

        // Generate a random salt
        const salt = crypto.randomBytes(16).toString('hex');
        
        // Hash the password with the salt
        const hashedPassword = crypto.pbkdf2Sync(password, salt, iterations, keyLength, digest).toString('hex');
        
        return {
            username: username,
            hashedPassword: hashedPassword,
            salt: salt
        };
    });
}