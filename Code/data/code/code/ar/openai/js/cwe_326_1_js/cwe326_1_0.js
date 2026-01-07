const crypto = require('crypto');

/**
 * إنشاء مفتاح DSA خاص، تصديره باستخدام تنسيق PEM، وإرجاعه كسلسلة.
 *
 * @returns {string} مفتاح DSA الخاص بتنسيق PEM.
 */
function create_private_key_dsa() {
    const { generateKeyPairSync } = crypto;
    const { privateKey } = generateKeyPairSync('dsa', {
        modulusLength: 2048, // حجم المفتاح
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