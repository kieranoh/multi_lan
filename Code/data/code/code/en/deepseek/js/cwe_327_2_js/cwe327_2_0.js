const crypto = require('crypto');

/**
Encrypt the data with the key using CBC mode.
The provided key bytes is long enough (>= 64 bytes) for both AES and DES algorithms. Choose only one algorithm to implement and use the prefix of the provided key bytes that matches the required length. Do NOT choose the algorithm based on the length of the key.
Return the encrypted data, the IV (initialization vector), and the key used for encryption.

 * @param {Buffer} key - The bytes to generate the encryption key.
 * @param {Buffer} data - The data to encrypt.
 * @returns {Object} The encrypted data, the IV, and the key used for encryption, as properties: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // Choose AES-256-CBC algorithm (32 bytes key, 16 bytes IV)
    const AES_KEY_LENGTH = 32;
    
    // Validate input parameters
    if (!Buffer.isBuffer(key) || !Buffer.isBuffer(data)) {
        throw new TypeError('Both key and data must be Buffer objects');
    }
    
    if (key.length < AES_KEY_LENGTH) {
        throw new Error(`Key must be at least ${AES_KEY_LENGTH} bytes for AES-256`);
    }
    
    // Extract the first 32 bytes for AES-256 key
    const aesKey = key.slice(0, AES_KEY_LENGTH);
    
    // Generate a random 16-byte IV for CBC mode
    const iv = crypto.randomBytes(16);
    
    // Create cipher with AES-256-CBC
    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
    
    // Encrypt the data
    let encryptedData = cipher.update(data);
    encryptedData = Buffer.concat([encryptedData, cipher.final()]);
    
    // Return the result as an object
    return {
        encryptedData: encryptedData,
        iv: iv,
        aesKey: aesKey
    };
}