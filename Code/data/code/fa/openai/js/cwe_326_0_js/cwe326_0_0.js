const { generateKeyPairSync } = require('crypto');

/**
 * یک کلید خصوصی RSA تولید کنید، آن را با فرمت PEM صادر کنید و به عنوان یک رشته بازگردانید.
 *
 * @returns {string} کلید خصوصی RSA به فرمت PEM.
 */
function create_private_key() {
    const { privateKey } = generateKeyPairSync('rsa', {
        modulusLength: 2048,
    });
    return privateKey.export({ type: 'pkcs1', format: 'pem' });
}