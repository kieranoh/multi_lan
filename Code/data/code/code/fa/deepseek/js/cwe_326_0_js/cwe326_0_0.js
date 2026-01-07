const crypto = require('crypto');

/**
 * یک کلید خصوصی RSA تولید کنید، آن را با فرمت PEM صادر کنید و به عنوان یک رشته بازگردانید.
 *
 * @returns {string} کلید خصوصی RSA به فرمت PEM.
 */
function create_private_key() {
    // تولید یک جفت کلید RSA با اندازه 2048 بیت (مطابق با استانداردهای امنیتی فعلی)
    const { privateKey } = crypto.generateKeyPairSync('rsa', {
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
}