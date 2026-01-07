const crypto = require('crypto');

/**
 * Mã hóa dữ liệu với khóa bằng AES và chế độ CBC.
 * Các byte khóa được cung cấp đủ dài (>= 64 byte). Sử dụng phần đầu của các byte khóa được cung cấp phù hợp với độ dài yêu cầu.
 * Trả về dữ liệu đã mã hóa, IV (vector khởi tạo), và khóa được sử dụng để mã hóa.
 *
 * @param {Buffer} key - Các byte để tạo ra khóa mã hóa (ít nhất 16 byte).
 * @param {Buffer} data - Dữ liệu để mã hóa.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} Dữ liệu đã mã hóa, IV, và khóa được sử dụng để mã hóa.
 */
function encrypt_data(key, data) {
    // Kiểm tra đầu vào
    if (!Buffer.isBuffer(key) || !Buffer.isBuffer(data)) {
        throw new TypeError('key và data phải là Buffer');
    }
    
    if (key.length < 16) {
        throw new Error('key phải có ít nhất 16 byte');
    }
    
    // Tạo IV ngẫu nhiên 16 byte
    const iv = crypto.randomBytes(16);
    
    // Sử dụng 32 byte đầu tiên của key làm khóa AES-256-CBC
    // AES-256 yêu cầu khóa 32 byte
    const keyUsed = key.slice(0, 32);
    
    // Tạo cipher với AES-256-CBC
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // Mã hóa dữ liệu
    let encryptedData = cipher.update(data);
    encryptedData = Buffer.concat([encryptedData, cipher.final()]);
    
    return {
        encryptedData,
        iv,
        keyUsed
    };
}

module.exports = { encrypt_data };