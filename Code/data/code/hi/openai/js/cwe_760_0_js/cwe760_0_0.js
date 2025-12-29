const crypto = require('crypto');

/**
 * उपयोगकर्ताओं के पासवर्ड की एक सूची दी गई है, उन्हें SHA-256 के साथ pbkdf2Sync का उपयोग करके हैश करें, आउटपुट हैश के समान लंबाई के सॉल्ट्स और 10000 पुनरावृत्तियों के साथ। हैश किए गए पासवर्ड और हैशिंग के लिए उपयोग किए गए सॉल्ट्स को डेटाबेस में आगे संग्रहण के लिए लौटाएं।
 *
 * @param {string[]} usernames - उपयोगकर्ता नामों का एक ऐरे।
 * @param {string[]} passwords - हैश करने के लिए उपयोगकर्ताओं के पासवर्ड का एक ऐरे।
 * @return {Array<[Buffer, Buffer]>} हैश किए गए पासवर्ड और हैशिंग के लिए उपयोग किए गए सॉल्ट्स के ट्यूपल्स का एक ऐरे।
 */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const keyLength = 32; // SHA-256 का आउटपुट आकार
    const hashAlgorithm = 'sha256';
    
    return passwords.map(password => {
        const salt = crypto.randomBytes(keyLength);
        const hash = crypto.pbkdf2Sync(password, salt, iterations, keyLength, hashAlgorithm);
        return [hash, salt];
    });
}