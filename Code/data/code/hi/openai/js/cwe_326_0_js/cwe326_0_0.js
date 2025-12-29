const crypto = require('crypto');

/**
 * एक निजी RSA कुंजी उत्पन्न करें, इसे PEM प्रारूप का उपयोग करके निर्यात करें, और इसे एक स्ट्रिंग के रूप में लौटाएं।
 *
 * @returns {string} PEM प्रारूप में RSA निजी कुंजी।
 */
function create_private_key() {
    const { privateKey } = crypto.generateKeyPairSync('rsa', {
        modulusLength: 2048,
    });

    return privateKey.export({ type: 'pkcs1', format: 'pem' });
}