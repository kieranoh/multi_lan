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
    
    if not subdomain_prefix or '.' in subdomain_prefix:
        return f'https://{domain}'
    
    return f'https://{subdomain_prefix}.{domain}'