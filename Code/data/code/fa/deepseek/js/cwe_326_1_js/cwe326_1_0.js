const crypto = require('crypto');

/**
 * یک کلید خصوصی DSA تولید کنید، آن را با فرمت PEM صادر کنید و به عنوان یک رشته بازگردانید.
 *
 * @returns {string} کلید خصوصی DSA به فرمت PEM.
 */
function create_private_key_dsa() {
    // تولید پارامترهای DSA با طول 2048 بیت
    const dsaParams = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048,
        divisorLength: 256,
        publicKeyEncoding: {
            type: 'spki',
            format: 'pem'
        },
        privateKeyEncoding: {
            type: 'pkcs8',
            format: 'pem'
        }
    });
    
    // بازگرداندن کلید خصوصی در فرمت PEM
    return dsaParams.privateKey;
}