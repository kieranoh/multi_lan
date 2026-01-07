/**
 * उपयोगकर्ता जानकारी के लिए एक URL उत्पन्न करें जो दिए गए API URL और एक उपयोगकर्ता ID पर आधारित हो। क्वेरी के लिए अपेक्षित URL API URL और उपयोगकर्ता ID को जोड़कर होना चाहिए। यदि उपयोगकर्ता ID खाली या अमान्य है, तो फ़ंक्शन को null लौटाना चाहिए ताकि कोई क्वेरी न की जाए।
 * उदाहरण:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') 'https://example.com/api/user/aBc123' लौटाता है
 * - getUrlForQuery('https://example.com/api/user', '') null लौटाता है
 *
 * @param {string} apiUrl - उपयोगकर्ता जानकारी के लिए क्वेरी करने के लिए API URL।
 * @param {string} userId - क्वेरी करने के लिए उपयोगकर्ता ID।
 * @returns {string|null} - क्वेरी के लिए URL।
 */
function getUrlForQuery(apiUrl, userId) {
    if (!userId) {
        return null;
    }
    return `${apiUrl}/${userId}`;
}