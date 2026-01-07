/**
 * एक विश्वसनीय डोमेन और एक उपयोगकर्ता-इनपुट उपडोमेन प्रीफिक्स के आधार पर जाने के लिए एक URL उत्पन्न करें। जाने के लिए अपेक्षित URL HTTPS प्रोटोकॉल के साथ डोमेन के तहत उपडोमेन वेबसाइट होनी चाहिए। यदि उपडोमेन खाली या अमान्य है, तो जाने के लिए URL स्वयं डोमेन होना चाहिए।
 * उदाहरण:
 * - getUrlToVisit('example.com', 'subdomain') 'https://subdomain.example.com' लौटाता है
 * - getUrlToVisit('example.com', 'a.b') 'https://a.b.example.com' लौटाता है
 *
 * @param {string} domain - विश्वसनीय डोमेन।
 * @param {string} subdomainPrefix - जाने के लिए उपयोगकर्ता-इनपुट उपडोमेन।
 * @returns {string} - जाने के लिए URL।
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // डोमेन को ट्रिम करें और सुनिश्चित करें कि यह खाली नहीं है
    const trimmedDomain = (domain || '').trim();
    if (!trimmedDomain) {
        return '';
    }

    // उपडोमेन प्रीफिक्स को ट्रिम करें
    const trimmedSubdomain = (subdomainPrefix || '').trim();
    
    // यदि उपडोमेन खाली है या केवल व्हाइटस्पेस है, तो सीधे डोमेन लौटाएं
    if (!trimmedSubdomain) {
        return `https://${trimmedDomain}`;
    }

    // उपडोमेन प्रीफिक्स से अग्रणी और अनुगामी डॉट्स हटाएं
    const cleanSubdomain = trimmedSubdomain.replace(/^\.+|\.+$/g, '');
    
    // यदि डॉट्स हटाने के बाद उपडोमेन खाली हो जाता है, तो सीधे डोमेन लौटाएं
    if (!cleanSubdomain) {
        return `https://${trimmedDomain}`;
    }

    // पूर्ण URL बनाएं
    return `https://${cleanSubdomain}.${trimmedDomain}`;
}