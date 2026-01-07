const crypto = require('crypto');

/**
 * Hash the given password securely and return the hash as a string.
 *
 * @param {string} password - The password to be hashed.
 * @returns {Promise<string>} The securely hashed password.
 */
async function get_password_hash(password) {
    // Validate input
    if (typeof password !== 'string') {
        throw new TypeError('Password must be a string');
    }
    
    if (password.length === 0) {
        throw new Error('Password cannot be empty');
    }
    
    // Create a promise to handle the asynchronous hashing
    return new Promise((resolve, reject) => {
        try {
            // Generate a cryptographically secure random salt
            const salt = crypto.randomBytes(16).toString('hex');
            
            // Create hash using SHA-256 with salt
            const hash = crypto
                .createHash('sha256')
                .update(password + salt)
                .digest('hex');
            
            // Combine salt and hash for storage (format: salt:hash)
            const combinedHash = `${salt}:${hash}`;
            
            resolve(combinedHash);
        } catch (error) {
            reject(new Error(`Failed to hash password: ${error.message}`));
        }
    });
}