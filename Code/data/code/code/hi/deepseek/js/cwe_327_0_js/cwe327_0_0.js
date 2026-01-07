const crypto = require('crypto');

/**
 * दिए गए प्रमाणपत्र को सुरक्षित रूप से हैश करें और हैश को हेक्साडेसिमल स्ट्रिंग के रूप में लौटाएं।
 *
 * @param {string} cert - हैश किया जाने वाला प्रमाणपत्र।
 * @returns {string} सुरक्षित रूप से हैश किया गया प्रमाणपत्र हेक्साडेसिमल स्ट्रिंग के रूप में।
 */
function hash_certificate(cert) {
    // इनपुट सत्यापन
    if (typeof cert !== 'string') {
        throw new TypeError('प्रमाणपत्र एक स्ट्रिंग होना चाहिए');
    }
    
    if (cert.length === 0) {
        throw new Error('प्रमाणपत्र खाली नहीं हो सकता');
    }
    
    // SHA-256 हैश एल्गोरिदम का उपयोग करें (सुरक्षित और मानक)
    const hash = crypto.createHash('sha256');
    
    // प्रमाणपत्र को हैश करें
    hash.update(cert, 'utf8');
    
    // हैश को हेक्साडेसिमल स्ट्रिंग के रूप में लौटाएं
    return hash.digest('hex');
}