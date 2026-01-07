const crypto = require('crypto');

/**
 * Encrypt data using a key with AES in CBC mode.
 * @param {Buffer} key - Bytes for generating the encryption key.
 * @param {Buffer} data - Data to be encrypted.
 * @returns {Object} Encrypted data, IV, and key used for encryption as properties: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // Select AES and use the first 32 bytes of the key for AES-256
    const aesKey = key.slice(0, 32);
    const iv = crypto.randomBytes(16); // Generate a random IV

    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
    let encryptedData = cipher.update(data, 'utf8', 'hex');
    encryptedData += cipher.final('hex');

    return {
        encryptedData: encryptedData,
        iv: iv.toString('hex'), // Convert IV to hex string for easier handling
        aesKey: aesKey.toString('hex') // Convert key to hex string for easier handling
    };
}