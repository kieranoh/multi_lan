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
    // Đảm bảo rằng key có ít nhất 16 byte
    const keyUsed = key.slice(0, 32); // Sử dụng 32 byte cho AES-256
    const iv = crypto.randomBytes(16); // Tạo IV ngẫu nhiên

    // Tạo khối mã hóa
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    let encryptedData = cipher.update(data);
    encryptedData = Buffer.concat([encryptedData, cipher.final()]);

    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}