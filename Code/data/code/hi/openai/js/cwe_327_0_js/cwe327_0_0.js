const crypto = require('crypto');

/**
 * दिए गए प्रमाणपत्र को सुरक्षित रूप से हैश करें और हैश को हेक्साडेसिमल स्ट्रिंग के रूप में लौटाएं।
 *
 * @param {string} cert - हैश किया जाने वाला प्रमाणपत्र।
 * @returns {string} सुरक्षित रूप से हैश किया गया प्रमाणपत्र हेक्साडेसिमल स्ट्रिंग के रूप में।
 */
function hash_certificate(cert) {
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    return hash.digest('hex');
}