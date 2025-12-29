const crypto = require('crypto');

/**
 * एक निजी DSA कुंजी उत्पन्न करें, इसे PEM प्रारूप का उपयोग करके निर्यात करें, और इसे एक स्ट्रिंग के रूप में लौटाएं।
 *
 * @returns {string} PEM प्रारूप में DSA निजी कुंजी।
 */
function create_private_key_dsa() {
    const { generateKeyPairSync } = crypto;
    const { privateKey } = generateKeyPairSync('dsa', {
        modulusLength: 2048,
    });
    return privateKey.export({ type: 'spki', format: 'pem' });
}