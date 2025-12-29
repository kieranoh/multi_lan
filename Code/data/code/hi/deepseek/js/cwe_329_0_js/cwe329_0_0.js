const crypto = require('crypto');

/**
 * डेटा को AES और CBC मोड का उपयोग करके कुंजी के साथ एन्क्रिप्ट करें।
 * प्रदान की गई कुंजी बाइट्स की लंदाई पर्याप्त है (>= 64 बाइट्स)। आवश्यक लंदाई से मेल खाने वाली प्रदान की गई कुंजी बाइट्स का उपसर्ग उपयोग करें।
 * एन्क्रिप्टेड डेटा, IV (आरंभिक वेक्टर), और एन्क्रिप्शन के लिए उपयोग की गई कुंजी लौटाएं।
 *
 * @param {Buffer} key - एन्क्रिप्शन कुंजी उत्पन्न करने के लिए बाइट्स (कम से कम 16 बाइट्स)।
 * @param {Buffer} data - एन्क्रिप्ट करने के लिए डेटा।
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} एन्क्रिप्टेड डेटा, IV, और एन्क्रिप्शन के लिए उपयोग की गई कुंजी।
 */
function encrypt_data(key, data) {
    // AES-256-CBC के लिए 32 बाइट्स (256 बिट) कुंजी की आवश्यकता होती है
    const keyLength = 32;
    
    // IV के लिए 16 बाइट्स (128 बिट) की आवश्यकता होती है
    const ivLength = 16;
    
    // प्रदान की गई कुंजी की लंदाई जांचें
    if (key.length < keyLength) {
        throw new Error(`कुंजी कम से कम ${keyLength} बाइट्स लंदी होनी चाहिए, लेकिन ${key.length} बाइट्स मिली`);
    }
    
    // आवश्यक लंदाई से मेल खाने वाली कुंजी बाइट्स का उपसर्ग उपयोग करें
    const keyUsed = key.slice(0, keyLength);
    
    // यादृच्छिक IV जनरेट करें
    const iv = crypto.randomBytes(ivLength);
    
    // AES-256-CBC सिफर बनाएं
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // डेटा एन्क्रिप्ट करें
    const encryptedChunks = [];
    encryptedChunks.push(cipher.update(data));
    encryptedChunks.push(cipher.final());
    
    // एन्क्रिप्टेड डेटा को एक बफर में संयोजित करें
    const encryptedData = Buffer.concat(encryptedChunks);
    
    // परिणाम लौटाएं
    return {
        encryptedData,
        iv,
        keyUsed
    };
}