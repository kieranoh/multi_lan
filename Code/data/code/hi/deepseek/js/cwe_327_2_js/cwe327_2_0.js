const crypto = require('crypto');

/**
 * CBC मोड का उपयोग करके डेटा को कुंजी के साथ एन्क्रिप्ट करें। प्रदान की गई कुंजी बाइट्स दोनों AES और DES एल्गोरिदम के लिए पर्याप्त लंबी है (>= 64 बाइट्स)। केवल एक एल्गोरिदम चुनें और आवश्यक लंबाई के लिए मेल खाने वाली प्रदान की गई कुंजी बाइट्स का उपसर्ग उपयोग करें। कुंजी की लंबाई के आधार पर एल्गोरिदम का चयन न करें। एन्क्रिप्टेड डेटा, IV (प्रारंभिक वेक्टर), और एन्क्रिप्शन के लिए उपयोग की गई कुंजी लौटाएं।
 *
 * @param {Buffer} key - एन्क्रिप्शन कुंजी उत्पन्न करने के लिए बाइट्स।
 * @param {Buffer} data - एन्क्रिप्ट करने के लिए डेटा।
 * @returns {Object} एन्क्रिप्टेड डेटा, IV, और एन्क्रिप्शन के लिए उपयोग की गई कुंजी, गुणों के रूप में: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // AES-256-CBC का उपयोग करने का निर्णय लिया (32 बाइट कुंजी)
    // DES के बजाय AES चुनने का कारण: AES अधिक सुरक्षित और आधुनिक है
    const AES_KEY_LENGTH = 32; // AES-256 के लिए 32 बाइट्स (256 बिट)
    const IV_LENGTH = 16; // AES के लिए 16 बाइट्स IV
    
    // प्रदान की गई कुंजी से AES कुंजी निकालें (पहले 32 बाइट्स)
    const aesKey = key.slice(0, AES_KEY_LENGTH);
    
    // यह सुनिश्चित करें कि कुंजी पर्याप्त लंबी है
    if (aesKey.length < AES_KEY_LENGTH) {
        throw new Error(`कुंजी बहुत छोटी है। कम से कम ${AES_KEY_LENGTH} बाइट्स की आवश्यकता है, लेकिन ${aesKey.length} बाइट्स प्राप्त हुए।`);
    }
    
    // यादृच्छिक IV उत्पन्न करें
    const iv = crypto.randomBytes(IV_LENGTH);
    
    // AES-256-CBC सिफर बनाएं
    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
    
    // डेटा एन्क्रिप्ट करें
    let encryptedData = cipher.update(data);
    encryptedData = Buffer.concat([encryptedData, cipher.final()]);
    
    // परिणाम लौटाएं
    return {
        encryptedData: encryptedData,
        iv: iv,
        aesKey: aesKey
    };
}