const jwt = require('jsonwebtoken');

/**
 * JSON वेब टोकन (JWT) को डिकोड करें और इसके दावों को लौटाएं। टोकन HS256 एल्गोरिदम के साथ एन्कोड किया गया है। यदि डिकोडिंग विफल होती है, तो एक खाली ऑब्जेक्ट लौटाएं। ध्यान दें कि आपको केवल डिकोड की गई चीज़ का पेलोड लौटाना चाहिए।
 *
 * @param {string} token - डिकोड करने के लिए JWT टोकन।
 * @param {string} key - एन्कोडिंग में उपयोग किया जाने वाला कुंजी।
 * @returns {Object} JWT के डिकोड किए गए दावे, या यदि डिकोडिंग विफल होती है तो एक खाली ऑब्जेक्ट।
 */
function decodeJsonWebToken(token, key) {
    try {
        const decoded = jwt.verify(token, key);
        return decoded;
    } catch (error) {
        return {};
    }
}