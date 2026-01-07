const { generateKeyPairSync } = require('crypto');

/* * إنشاء مفتاح RSA خاص، تصديره باستخدام تنسيق PEM، وإرجاعه كسلسلة.
 *
 * @returns {string} مفتاح RSA الخاص بتنسيق PEM. */
function create_private_key() {
    const { privateKey } = generateKeyPairSync('rsa', {
        modulusLength: 2048,
    });

    return privateKey.export({ type: 'pkcs1', format: 'pem' });
}