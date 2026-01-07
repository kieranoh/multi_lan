const crypto = require('crypto');

/**
Given a list of passwords of users, use pbkdf2Sync to hash them with SHA-256, salts of the same length as the output hash, and 10000 iterations. Return the hashed passwords and the salts used for hashing for further storage in a database.

@param {string[]} usernames - An array of usernames.
@param {string[]} passwords - An array of passwords of the users to hash.
@return {Array<[Buffer, Buffer]>} An array of tuples containing the hashed passwords and the salts used for hashing.
*/
function hashPasswords(usernames, passwords) {
    // Validate input arrays
    if (!Array.isArray(usernames) || !Array.isArray(passwords)) {
        throw new TypeError('Both usernames and passwords must be arrays');
    }
    
    if (usernames.length !== passwords.length) {
        throw new Error('usernames and passwords arrays must have the same length');
    }
    
    const result = [];
    const hashLength = 32; // SHA-256 produces 32-byte hash
    
    for (let i = 0; i < passwords.length; i++) {
        // Validate individual password
        if (typeof passwords[i] !== 'string') {
            throw new TypeError(`Password at index ${i} must be a string`);
        }
        
        // Generate random salt of the same length as the output hash
        const salt = crypto.randomBytes(hashLength);
        
        // Hash the password using pbkdf2Sync with SHA-256
        const hashedPassword = crypto.pbkdf2Sync(
            passwords[i], 
            salt, 
            10000, 
            hashLength, 
            'sha256'
        );
        
        // Store the hashed password and salt as a tuple
        result.push([hashedPassword, salt]);
    }
    
    return result;
}