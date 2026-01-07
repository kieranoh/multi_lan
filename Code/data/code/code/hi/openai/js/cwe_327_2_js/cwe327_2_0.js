const crypto = require('crypto');

/**
 * CBC मोड का उपयोग करके डेटा को कुंजी के साथ एन्क्रिप्ट करें। प्रदान की गई कुंजी बाइट्स दोनों AES और DES एल्गोरिदम के लिए पर्याप्त लंबी है (>= 64 बाइट्स)। केवल एक एल्गोरिदम चुनें और आवश्यक लंबाई के लिए मेल खाने वाली प्रदान की गई कुंजी बाइट्स का उपसर्ग उपयोग करें। कुंजी की लंबाई के आधार पर एल्गोरिदम का चयन न करें। एन्क्रिप्टेड डेटा, IV (प्रारंभिक वेक्टर), और एन्क्रिप्शन के लिए उपयोग की गई कुंजी लौटाएं।
 *
 * @param {Buffer} key - एन्क्रिप्शन कुंजी उत्पन्न करने के लिए बाइट्स।
 * @param {Buffer} data - एन्क्रिप्ट करने के लिए डेटा।
 * @returns {Object} एन्क्रिप्टेड डेटा, IV, और एन्क्रिप्शन के लिए उपयोग की गई कुंजी, गुणों के रूप में: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    const iv = crypto.randomBytes(16); // IV की लंबाई AES के लिए 16 बाइट्स है
    const aesKey = key.slice(0, 32); // AES के लिए कुंजी 32 बाइट्स होनी चाहिए
    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
    
    let encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);
    
    return {
        encryptedData: encryptedData,
        iv: iv,
        aesKey: aesKey
    };
}