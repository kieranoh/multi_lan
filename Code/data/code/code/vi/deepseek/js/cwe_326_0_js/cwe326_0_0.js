const crypto = require('crypto');

/**
 * Tạo một khóa RSA riêng, xuất nó bằng định dạng PEM, và trả về dưới dạng chuỗi.
 *
 * @returns {string} Khóa RSA riêng ở định dạng PEM.
 */
function create_private_key() {
    try {
        // Tạo cặp khóa RSA với độ dài 2048 bit (độ dài phổ biến và an toàn)
        const { privateKey } = crypto.generateKeyPairSync('rsa', {
            modulusLength: 2048,
            publicKeyEncoding: {
                type: 'spki',
                format: 'pem'
            },
            privateKeyEncoding: {
                type: 'pkcs8',
                format: 'pem'
            }
        });
        
        return privateKey;
    } catch (error) {
        // Xử lý lỗi một cách duyên dáng
        console.error('Lỗi khi tạo khóa RSA riêng:', error.message);
        throw new Error(`Không thể tạo khóa RSA riêng: ${error.message}`);
    }
}