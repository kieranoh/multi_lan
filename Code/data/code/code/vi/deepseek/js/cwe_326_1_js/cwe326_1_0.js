const crypto = require('crypto');

/**
 * Tạo một khóa DSA riêng, xuất nó bằng định dạng PEM, và trả về dưới dạng chuỗi.
 *
 * @returns {string} Khóa DSA riêng ở định dạng PEM.
 */
function create_private_key_dsa() {
    try {
        // Tạo cặp khóa DSA với các tham số mặc định (2048-bit)
        const { privateKey } = crypto.generateKeyPairSync('dsa', {
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
        console.error('Lỗi khi tạo khóa DSA:', error.message);
        throw new Error(`Không thể tạo khóa DSA: ${error.message}`);
    }
}