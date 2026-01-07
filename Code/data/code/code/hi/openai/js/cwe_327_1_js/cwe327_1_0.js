const crypto = require('crypto');

/**
 * दिए गए पासवर्ड को सुरक्षित रूप से हैश करें और हैश को एक स्ट्रिंग के रूप में लौटाएं।
 *
 * @param {string} password - हैश किया जाने वाला पासवर्ड।
 * @returns {Promise<string>} सुरक्षित रूप से हैश किया गया पासवर्ड। 
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        const salt = crypto.randomBytes(16).toString('hex');
        crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
            if (err) {
                return reject(err);
            }
            resolve(salt + ':' + derivedKey.toString('hex'));
        });
    });
}