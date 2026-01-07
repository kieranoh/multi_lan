const crypto = require('crypto');

/**
 * एक निजी DSA कुंजी उत्पन्न करें, इसे PEM प्रारूप का उपयोग करके निर्यात करें, और इसे एक स्ट्रिंग के रूप में लौटाएं।
 *
 * @returns {string} PEM प्रारूप में DSA निजी कुंजी।
 */
function create_private_key_dsa() {
    // DSA कुंजी जोड़ी उत्पन्न करें
    const { privateKey } = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048, // DSA के लिए सामान्य मापदंड
        divisorLength: 256,  // q की लंबाई (बिट्स में)
    });
    
    // निजी कुंजी को PEM प्रारूप में निर्यात करें
    const privateKeyPem = privateKey.export({
        format: 'pem',
        type: 'pkcs8'
    });
    
    return privateKeyPem;
}