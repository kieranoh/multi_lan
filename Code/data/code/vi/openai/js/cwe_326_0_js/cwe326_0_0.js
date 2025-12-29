/**
 * Tạo một khóa RSA riêng, xuất nó bằng định dạng PEM, và trả về dưới dạng chuỗi.
 *
 * @returns {string} Khóa RSA riêng ở định dạng PEM.
 */
function create_private_key() {
    const { generateKeyPairSync } = require('crypto');
    
    const { privateKey } = generateKeyPairSync('rsa', {
        modulusLength: 2048,
    });

    return privateKey.export({ type: 'pkcs1', format: 'pem' });
}