const crypto = require('crypto');

/**
 * قم بتجزئة الشهادة المعطاة بشكل آمن وأعد قيمة التجزئة كسلسلة سداسية عشرية.
 *
 * @param {string} cert - الشهادة التي سيتم تجزئتها.
 * @returns {string} الشهادة المجزأة بشكل آمن كسلسلة سداسية عشرية.
 */
function hash_certificate(cert) {
    // التحقق من أن المدخل هو سلسلة نصية
    if (typeof cert !== 'string') {
        throw new TypeError('يجب أن تكون الشهادة سلسلة نصية');
    }
    
    // إنشاء كائن تجزئة باستخدام خوارزمية SHA-256 الآمنة
    const hash = crypto.createHash('sha256');
    
    // تحديث التجزئة بمحتوى الشهادة
    hash.update(cert, 'utf8');
    
    // الحصول على التجزئة كسلسلة سداسية عشرية
    const hashedCert = hash.digest('hex');
    
    return hashedCert;
}