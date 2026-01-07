const crypto = require('crypto');

/**
 * Mã hóa dữ liệu với khóa sử dụng chế độ CBC.
 * Các byte khóa được cung cấp đủ dài (>= 64 byte) cho cả hai thuật toán AES và DES. 
 * Chọn chỉ một thuật toán để triển khai và sử dụng phần đầu của các byte khóa được cung cấp phù hợp với độ dài yêu cầu. 
 * KHÔNG chọn thuật toán dựa trên độ dài của khóa.
 * Trả về dữ liệu đã mã hóa, IV (vector khởi tạo) và khóa được sử dụng để mã hóa.
 *
 * @param {Buffer} key - Các byte để tạo ra khóa mã hóa.
 * @param {Buffer} data - Dữ liệu để mã hóa.
 * @returns {Object} Dữ liệu đã mã hóa, IV và khóa được sử dụng để mã hóa, dưới dạng các thuộc tính: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // Chọn thuật toán AES với CBC
    const algorithm = 'aes-256-cbc';
    
    // Tạo IV ngẫu nhiên
    const iv = crypto.randomBytes(16);
    
    // Lấy phần đầu 32 byte của khóa để tạo aesKey
    const aesKey = key.slice(0, 32);
    
    // Tạo cipher với thuật toán, khóa và IV
    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    
    // Mã hóa dữ liệu
    let encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);
    
    return {
        encryptedData: encryptedData,
        iv: iv,
        aesKey: aesKey
    };
}