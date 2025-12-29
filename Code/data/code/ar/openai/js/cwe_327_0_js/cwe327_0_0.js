const crypto = require('crypto');

/* * قم بتجزئة الشهادة المعطاة بشكل آمن وأعد قيمة التجزئة كسلسلة سداسية عشرية.
 *
 * @param {string} cert - الشهادة التي سيتم تجزئتها.
 * @returns {string} الشهادة المجزأة بشكل آمن كسلسلة سداسية عشرية. */
function hash_certificate(cert) {
    const hash = crypto.createHash('sha256'); // استخدام خوارزمية SHA-256
    hash.update(cert); // تحديث التجزئة بالشهادة
    return hash.digest('hex'); // إرجاع التجزئة كسلسلة سداسية عشرية
}