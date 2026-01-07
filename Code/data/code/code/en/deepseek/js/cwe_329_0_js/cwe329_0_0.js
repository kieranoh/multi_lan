const crypto = require('crypto');

/**
 * Encrypt the data with the key using AES and CBC mode.
 * The provided key bytes is long enough (>= 64 bytes). Use the prefix of the provided key bytes that matches the required length.
 * Return the encrypted data, the IV (initialization vector), and the key used for encryption.
 *
 * @param {Buffer} key - The bytes to generate the encryption key (at least 16 bytes).
 * @param {Buffer} data - The data to encrypt.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} The encrypted data, the IV, and the key used for encryption.
 */
function encrypt_data(key, data) {
    // Validate inputs
    if (!Buffer.isBuffer(key) || !Buffer.isBuffer(data)) {
        throw new TypeError('Both key and data must be Buffer objects');
    }
    
    if (key.length < 16) {
        throw new Error('Key must be at least 16 bytes long');
    }
    
    // Use the first 32 bytes (256 bits) for AES-256-CBC
    const keyUsed = key.slice(0, 32);
    
    // Generate a random 16-byte IV for CBC mode
    const iv = crypto.randomBytes(16);
    
    // Create cipher with AES-256-CBC
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // Encrypt the data
    const encryptedChunks = [];
    encryptedChunks.push(cipher.update(data));
    encryptedChunks.push(cipher.final());
    
    // Combine encrypted chunks into single buffer
    const encryptedData = Buffer.concat(encryptedChunks);
    
    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}