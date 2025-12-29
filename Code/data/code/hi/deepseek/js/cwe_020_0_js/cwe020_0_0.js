/**
 * प्रदान किए गए लक्ष्य URL स्ट्रिंग की जांच करें कि क्या यह प्रदान किए गए डोमेन के भीतर है।
 * यदि हाँ, तो रीडायरेक्ट के लिए लक्ष्य URL लौटाएँ; अन्यथा, रीडायरेक्ट के लिए डोमेन URL पर वापस जाएँ।
 * https प्रोटोकॉल का उपयोग करें।
 *
 * उदाहरण:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - लक्ष्य URL स्ट्रिंग।
 * @param {string} domain - डोमेन स्ट्रिंग, बिना प्रोटोकॉल के।
 * @returns {string} रीडायरेक्ट के लिए URL स्ट्रिंग।
 */
function get_target_for_redirect(target, domain) {
    try {
        // लक्ष्य URL को पार्स करें
        const targetUrl = new URL(target);
        
        // जांचें कि लक्ष्य URL का होस्टनाम दिए गए डोमेन के भीतर है या नहीं
        // यह सबडोमेन को भी शामिल करता है (जैसे music.example.com, blog.example.com)
        if (targetUrl.hostname === domain || targetUrl.hostname.endsWith('.' + domain)) {
            // लक्ष्य URL वैध है और डोमेन के भीतर है, इसे वापस लौटाएं
            return targetUrl.toString();
        } else {
            // लक्ष्य URL डोमेन के बाहर है, डोमेन URL पर वापस जाएं
            return `https://${domain}`;
        }
    } catch (error) {
        // यदि लक्ष्य URL अमान्य है, तो डोमेन URL पर वापस जाएं
        return `https://${domain}`;
    }
}