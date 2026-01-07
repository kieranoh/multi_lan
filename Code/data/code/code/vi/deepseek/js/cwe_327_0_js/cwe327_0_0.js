const crypto = require('crypto');

/**
 * Băm chứng chỉ đã cho một cách an toàn và trả về băm dưới dạng chuỗi thập lục phân.
 *
 * @param {string} cert - Chứng chỉ cần băm.
 * @returns {string} Chứng chỉ đã băm an toàn dưới dạng chuỗi thập lục phân.
 */
function hash_certificate(cert) {
    if (typeof cert !== 'string') {
        throw new TypeError('Đầu vào phải là một chuỗi');
    }
    
    if (cert.length === 0) {
        throw new Error('Chứng chỉ không được để trống');
    }
    
    try {
        // Tạo băm SHA-256 của chứng chỉ
        const hash = crypto.createHash('sha256');
        hash.update(cert, 'utf8');
        return hash.digest('hex');
    } catch (error) {
        throw new Error(`Không thể băm chứng chỉ: ${error.message}`);
    }
}

module.exports = { hash_certificate };