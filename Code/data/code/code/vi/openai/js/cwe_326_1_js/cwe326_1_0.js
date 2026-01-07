/**
 * Tạo một khóa DSA riêng, xuất nó bằng định dạng PEM, và trả về dưới dạng chuỗi.
 *
 * @returns {string} Khóa DSA riêng ở định dạng PEM.
 */
function create_private_key_dsa() {
    const { generateKeyPairSync } = require('crypto');

    // Tạo khóa DSA
    const { privateKey } = generateKeyPairSync('dsa', {
        modulusLength: 2048, // Chiều dài khóa
        publicKeyEncoding: {
            type: 'spki', // Kiểu mã hóa khóa công khai
            format: 'pem' // Định dạng PEM
        },
        privateKeyEncoding: {
            type: 'pkcs8', // Kiểu mã hóa khóa riêng
            format: 'pem' // Định dạng PEM
        }
    });

    return privateKey.toString('utf8'); // Trả về khóa DSA riêng ở định dạng PEM
}