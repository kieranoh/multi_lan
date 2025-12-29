const crypto = require('crypto');

/**
 * Verilen sertifikayı güvenli bir şekilde hash'le ve hash'i onaltılık bir dize olarak döndür.
 *
 * @param {string} cert - Hash'lenecek sertifika.
 * @returns {string} Güvenli bir şekilde hash'lenmiş sertifika onaltılık bir dize olarak.
 */
function hash_certificate(cert) {
    // Giriş doğrulama: cert parametresi string olmalı ve boş olmamalı
    if (typeof cert !== 'string') {
        throw new TypeError('Sertifika bir string olmalıdır');
    }
    
    if (cert.trim().length === 0) {
        throw new Error('Sertifika boş olamaz');
    }
    
    try {
        // SHA-256 hash algoritmasını kullanarak güvenli hash oluştur
        const hash = crypto.createHash('sha256');
        hash.update(cert, 'utf8');
        const hashedCert = hash.digest('hex');
        
        return hashedCert;
    } catch (error) {
        // Hash oluşturma sırasında oluşabilecek hataları ele al
        throw new Error(`Sertifika hash'lenirken bir hata oluştu: ${error.message}`);
    }
}