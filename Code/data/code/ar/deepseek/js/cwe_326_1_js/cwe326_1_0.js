const crypto = require('crypto');

/**
 * إنشاء مفتاح DSA خاص، تصديره باستخدام تنسيق PEM، وإرجاعه كسلسلة.
 *
 * @returns {string} مفتاح DSA الخاص بتنسيق PEM.
 */
function create_private_key_dsa() {
    // توليد زوج مفاتيح DSA باستخدام معلمات محددة
    const { privateKey } = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048, // طول المفتاح الموصى به للأمان
        divisorLength: 256,  // طول القاسم (يجب أن يكون 160 أو 224 أو 256)
    });
    
    // تصدير المفتاح الخاص بتنسيق PEM
    const pemPrivateKey = privateKey.export({
        type: 'pkcs8',
        format: 'pem',
    });
    
    return pemPrivateKey;
}