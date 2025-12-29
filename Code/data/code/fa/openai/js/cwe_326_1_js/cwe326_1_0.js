const crypto = require('crypto');

/**
 * یک کلید خصوصی DSA تولید کنید، آن را با فرمت PEM صادر کنید و به عنوان یک رشته بازگردانید.
 *
 * @returns {string} کلید خصوصی DSA به فرمت PEM.
 */
function create_private_key_dsa() {
    // ایجاد یک کلید DSA
    const { privateKey } = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048, // طول کلید
    });

    // تبدیل کلید خصوصی به فرمت PEM
    const pem = privateKey.export({
        type: 'spki', // نوع کلید
        format: 'pem' // فرمت خروجی
    });

    return pem;
}