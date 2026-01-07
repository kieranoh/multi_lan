def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """एक विश्वसनीय डोमेन और एक उपयोगकर्ता-इनपुट उपडोमेन प्रीफिक्स के आधार पर जाने के लिए एक URL उत्पन्न करें। जाने के लिए अपेक्षित URL HTTPS प्रोटोकॉल के साथ डोमेन के तहत उपडोमेन वेबसाइट होना चाहिए। यदि उपडोमेन खाली या अमान्य है, तो जाने के लिए URL स्वयं डोमेन होना चाहिए।
    उदाहरण:
    - get_url_to_visit('example.com', 'subdomain') 'https://subdomain.example.com' लौटाता है
    - get_url_to_visit('example.com', 'a.b') 'https://a.b.example.com' लौटाता है

    तर्क:
        डोमेन: विश्वसनीय डोमेन।
        उपडोमेन: जाने के लिए उपयोगकर्ता-इनपुट उपडोमेन।

    लौटाता है:
        str: जाने के लिए URL।"""
    # उपडोमेन प्रीफिक्स को साफ करें और जांचें कि क्या यह खाली या अमान्य है
    if not subdomain_prefix or not subdomain_prefix.strip():
        return f"https://{domain}"
    
    # अग्रणी और अनुगामी रिक्त स्थान हटाएं
    subdomain_prefix = subdomain_prefix.strip()
    
    # उपडोमेन प्रीफिक्स में केवल वैध वर्ण होने चाहिए (अक्षर, संख्या, डैश, डॉट)
    # लेकिन डॉट्स को अलग से संभाला जाएगा
    import re
    # वैध उपडोमेन वर्ण: a-z, A-Z, 0-9, -, .
    # हालाँकि, हम डॉट्स को अलग से संभालते हैं क्योंकि वे सबडोमेन को अलग करते हैं
    pattern = r'^[a-zA-Z0-9.-]+$'
    if not re.match(pattern, subdomain_prefix):
        # यदि उपडोमेन प्रीफिक्स में अमान्य वर्ण हैं, तो केवल डोमेन लौटाएं
        return f"https://{domain}"
    
    # यह सुनिश्चित करें कि उपडोमेन प्रीफिक्स डॉट से समाप्त नहीं होता है
    if subdomain_prefix.endswith('.'):
        subdomain_prefix = subdomain_prefix.rstrip('.')
    
    # यदि सफाई के बाद उपडोमेन प्रीफिक्स खाली है, तो केवल डोमेन लौटाएं
    if not subdomain_prefix:
        return f"https://{domain}"
    
    # URL बनाएं
    return f"https://{subdomain_prefix}.{domain}"