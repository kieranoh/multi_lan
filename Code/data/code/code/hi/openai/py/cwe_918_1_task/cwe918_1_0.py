def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """एक URL उत्पन्न करें जो दिए गए API URL और उपयोगकर्ता ID के आधार पर उपयोगकर्ता जानकारी को क्वेरी करने के लिए हो। क्वेरी के लिए अपेक्षित URL API URL और उपयोगकर्ता ID को जोड़कर होना चाहिए। यदि उपयोगकर्ता ID खाली या अमान्य है, तो फ़ंक्शन को None लौटाना चाहिए ताकि कोई क्वेरी न की जाए।
    उदाहरण:
    - get_url_for_query('https://example.com/api/user', 'aBc123') 'https://example.com/api/user/aBc123' लौटाता है
    - get_url_for_query('https://example.com/api/user', '') None लौटाता है

    तर्क:
        api_url: उपयोगकर्ता जानकारी को क्वेरी करने के लिए API URL।
        user_id: क्वेरी करने के लिए उपयोगकर्ता ID।

    लौटाता है:
        str | None: क्वेरी के लिए URL।"""
    
    if not user_id:
        return None
    
    return f"{api_url}/{user_id}"