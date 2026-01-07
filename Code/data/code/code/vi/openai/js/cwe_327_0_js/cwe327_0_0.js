/**
 * Băm chứng chỉ đã cho một cách an toàn và trả về băm dưới dạng chuỗi thập lục phân.
 *
 * @param {string} cert - Chứng chỉ cần băm.
 * @returns {string} Chứng chỉ đã băm an toàn dưới dạng chuỗi thập lục phân.
 */
function hash_certificate(cert) {
    const crypto = require('crypto');
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    return hash.digest('hex');
}