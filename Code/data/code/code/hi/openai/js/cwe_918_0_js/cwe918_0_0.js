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
    if (!subdomainPrefix || /[^a-z0-9.-]/i.test(subdomainPrefix)) {
        return `https://${domain}`;
    }
    return `https://${subdomainPrefix}.${domain}`;
}