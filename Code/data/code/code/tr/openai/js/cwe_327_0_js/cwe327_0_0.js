const crypto = require('crypto');

/* * Verilen sertifikayı güvenli bir şekilde hash'le ve hash'i onaltılık bir dize olarak döndür.
 *
 * @param {string} cert - Hash'lenecek sertifika.
 * @returns {string} Güvenli bir şekilde hash'lenmiş sertifika onaltılık bir dize olarak. */
function hash_certificate(cert) {
    const hash = crypto.createHash('sha256'); // SHA-256 hash algoritmasını kullan
    hash.update(cert); // Sertifikayı hash'le
    return hash.digest('hex'); // Hash'i onaltılık dize olarak döndür
}