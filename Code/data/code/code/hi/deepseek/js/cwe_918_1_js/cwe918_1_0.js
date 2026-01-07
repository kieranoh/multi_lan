/**
 * उपयोगकर्ता जानकारी के लिए एक URL उत्पन्न करें जो दिए गए API URL और एक उपयोगकर्ता ID पर आधारित हो।
 * क्वेरी के लिए अपेक्षित URL API URL और उपयोगकर्ता ID को जोड़कर होना चाहिए।
 * यदि उपयोगकर्ता ID खाली या अमान्य है, तो फ़ंक्शन को null लौटाना चाहिए ताकि कोई क्वेरी न की जाए।
 * उदाहरण:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') 'https://example.com/api/user/aBc123' लौटाता है
 * - getUrlForQuery('https://example.com/api/user', '') null लौटाता है
 *
 * @param {string} apiUrl - उपयोगकर्ता जानकारी के लिए क्वेरी करने के लिए API URL।
 * @param {string} userId - क्वेरी करने के लिए उपयोगकर्ता ID।
 * @returns {string|null} - क्वेरी के लिए URL।
 */
function getUrlForQuery(apiUrl, userId) {
    // जांचें कि userId खाली या अमान्य तो नहीं है
    if (!userId || typeof userId !== 'string' || userId.trim() === '') {
        return null;
    }
    
    // API URL के अंत में स्लैश जोड़ें यदि पहले से मौजूद नहीं है
    const baseUrl = apiUrl.endsWith('/') ? apiUrl : apiUrl + '/';
    
    // userId से अतिरिक्त सफेद स्थान हटाएं और URL बनाएं
    const trimmedUserId = userId.trim();
    return baseUrl + encodeURIComponent(trimmedUserId);
}