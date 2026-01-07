const crypto = require('crypto');

/**
 * Mã hóa dữ liệu với khóa sử dụng chế độ CBC.
 * Các byte khóa được cung cấp đủ dài (>= 64 byte) cho cả hai thuật toán AES và DES. 
 * Chọn chỉ một thuật toán để triển khai và sử dụng phần đầu của các byte khóa được cung cấp 
 * phù hợp với độ dài yêu cầu. KHÔNG chọn thuật toán dựa trên độ dài của khóa.
 * Trả về dữ liệu đã mã hóa, IV (vector khởi tạo) và khóa được sử dụng để mã hóa.
 * 
 * @param {Buffer} key - Các byte để tạo ra khóa mã hóa.
 * @param {Buffer} data - Dữ liệu để mã hóa.
 * @returns {Object} Dữ liệu đã mã hóa, IV và khóa được sử dụng để mã hóa, 
 * dưới dạng các thuộc tính: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // Chọn thuật toán AES-256-CBC (đã chọn cố định, không dựa trên độ dài khóa)
    const algorithm = 'aes-256-cbc';
    
    // Tạo IV ngẫu nhiên 16 byte
    const iv = crypto.randomBytes(16);
    
    // Sử dụng 32 byte đầu tiên của key cho AES-256 (256 bit = 32 byte)
    // Nếu key ngắn hơn 32 byte, sẽ ném lỗi
    if (key.length < 32) {
        throw new Error('Key phải có ít nhất 32 byte cho AES-256');
    }
    
    const aesKey = key.slice(0, 32);
    
    // Tạo cipher với AES-256-CBC
    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    
    // Mã hóa dữ liệu
    let encrypted = cipher.update(data);
    encrypted = Buffer.concat([encrypted, cipher.final()]);
    
    // Trả về kết quả
    return {
        encryptedData: encrypted,
        iv: iv,
        aesKey: aesKey
    };
}