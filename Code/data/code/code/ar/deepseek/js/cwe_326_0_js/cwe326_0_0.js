const crypto = require('crypto');

/**
 * إنشاء مفتاح RSA خاص، تصديره باستخدام تنسيق PEM، وإرجاعه كسلسلة.
 *
 * @returns {string} مفتاح RSA الخاص بتنسيق PEM.
 */
function create_private_key() {
    // إنشاء زوج مفاتيح RSA باستخدام 2048 بت (الحجم الموصى به)
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