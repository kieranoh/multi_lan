const crypto = require('crypto');

async function get_password_hash(password) {
    // Validate input
    if (typeof password !== 'string') {
        throw new TypeError('Password must be a string');
    }
    
    if (password.length === 0) {
        throw new Error('Password cannot be empty');
    }

    // Create a promise-based hash function
    return new Promise((resolve, reject) => {
        try {
            // Generate a cryptographically secure random salt
            const salt = crypto.randomBytes(16).toString('hex');
            
            // Use PBKDF2 with recommended parameters for password hashing
            crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
                if (err) {
                    reject(new Error('Failed to hash password: ' + err.message));
                    return;
                }
                
                // Combine salt and hash in a format that can be stored and verified later
                const hash = derivedKey.toString('hex');
                const result = `${salt}:${hash}`;
                resolve(result);
            });
        } catch (error) {
            reject(new Error('Failed to generate hash: ' + error.message));
        }
    });
}