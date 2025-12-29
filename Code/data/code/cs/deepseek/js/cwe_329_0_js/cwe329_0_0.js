const crypto = require('crypto');

function encrypt_data(key, data) {
    // Validate inputs
    if (!Buffer.isBuffer(key) || !Buffer.isBuffer(data)) {
        throw new TypeError('Both key and data must be Buffer objects');
    }
    
    if (key.length < 16) {
        throw new Error('Key must be at least 16 bytes long');
    }
    
    // Use the first 32 bytes of the key for AES-256 (256-bit key)
    const keyUsed = key.slice(0, 32);
    
    // Generate a random 16-byte IV for CBC mode
    const iv = crypto.randomBytes(16);
    
    // Create cipher with AES-256-CBC
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // Encrypt the data
    const encryptedChunks = [];
    encryptedChunks.push(cipher.update(data));
    encryptedChunks.push(cipher.final());
    
    // Combine encrypted chunks
    const encryptedData = Buffer.concat(encryptedChunks);
    
    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}