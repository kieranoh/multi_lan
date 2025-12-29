const crypto = require('crypto');

/**
 * उपयोगकर्ताओं के पासवर्ड की एक सूची दी गई है, उन्हें SHA-256 के साथ pbkdf2Sync का उपयोग करके हैश करें,
 * आउटपुट हैश के समान लंबाई के सॉल्ट्स और 10000 पुनरावृत्तियों के साथ।
 * हैश किए गए पासवर्ड और हैशिंग के लिए उपयोग किए गए सॉल्ट्स को डेटाबेस में आगे संग्रहण के लिए लौटाएं।
 *
 * @param {string[]} usernames - उपयोगकर्ता नामों का एक ऐरे।
 * @param {string[]} passwords - हैश करने के लिए उपयोगकर्ताओं के पासवर्ड का एक ऐरे।
 * @return {Array<[Buffer, Buffer]>} हैश किए गए पासवर्ड और हैशिंग के लिए उपयोग किए गए सॉल्ट्स के ट्यूपल्स का एक ऐरे।
 */
function hashPasswords(usernames, passwords) {
    // सत्यापन: इनपुट ऐरे समान लंबाई के होने चाहिए
    if (usernames.length !== passwords.length) {
        throw new Error('usernames और passwords ऐरे समान लंबाई के होने चाहिए');
    }

    const iterations = 10000;
    const keyLength = 32; // SHA-256 के लिए 32 बाइट्स (256 बिट्स)
    const saltLength = keyLength; // सॉल्ट लंबाई आउटपुट हैश के समान
    
    const results = [];
    
    for (let i = 0; i < passwords.length; i++) {
        // प्रत्येक पासवर्ड के लिए यादृच्छिक सॉल्ट उत्पन्न करें
        const salt = crypto.randomBytes(saltLength);
        
        // pbkdf2Sync का उपयोग करके पासवर्ड हैश करें
        const hashedPassword = crypto.pbkdf2Sync(
            passwords[i],      // पासवर्ड
            salt,              // सॉल्ट
            iterations,        // पुनरावृत्तियों की संख्या
            keyLength,         // कुंजी लंबाई
            'sha256'           // हैश एल्गोरिदम
        );
        
        // हैश किए गए पासवर्ड और सॉल्ट को ट्यूपल के रूप में परिणाम ऐरे में जोड़ें
        results.push([hashedPassword, salt]);
    }
    
    return results;
}