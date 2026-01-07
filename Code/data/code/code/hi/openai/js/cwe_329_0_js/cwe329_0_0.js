const crypto = require('crypto');

/**
 * डेटा को AES और CBC मोड का उपयोग करके कुंजी के साथ एन्क्रिप्ट करें।
 * प्रदान की गई कुंजी बाइट्स की लंबाई पर्याप्त है (>= 64 बाइट्स)। आवश्यक लंबाई से मेल खाने वाली प्रदान की गई कुंजी बाइट्स का उपसर्ग उपयोग करें।
 * एन्क्रिप्टेड डेटा, IV (आरंभिक वेक्टर), और एन्क्रिप्शन के लिए उपयोग की गई कुंजी लौटाएं।
 *
 * @param {Buffer} key - एन्क्रिप्शन कुंजी उत्पन्न करने के लिए बाइट्स (कम से कम 16 बाइट्स)।
 * @param {Buffer} data - एन्क्रिप्ट करने के लिए डेटा।
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} एन्क्रिप्टेड डेटा, IV, और एन्क्रिप्शन के लिए उपयोग की गई कुंजी।
 */
function encrypt_data(key, data) {
    // Ensure the key is 32 bytes long for AES-256
    const keyUsed = key.slice(0, 32);
    const iv = crypto.randomBytes(16); // Generate a random IV

    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    let encryptedData = cipher.update(data, 'utf8', 'hex');
    encryptedData += cipher.final('hex');

    return {
        encryptedData: Buffer.from(encryptedData, 'hex'),
        iv: iv,
        keyUsed: keyUsed
    };
}