import hashlib
import os
from typing import List, Tuple


def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''उपयोगकर्ताओं के पासवर्ड की एक सूची दी गई है, उन्हें SHA-256 के साथ हैश करने के लिए hashlib.pbkdf2_hmac का उपयोग करें, आउटपुट हैश के समान लंबाई के सॉल्ट्स और 10000 पुनरावृत्तियों के साथ। हैश किए गए पासवर्ड और हैशिंग के लिए उपयोग किए गए सॉल्ट्स को डेटाबेस में आगे संग्रहण के लिए लौटाएं।

    Args:
        usernames: उपयोगकर्ता नामों की एक सूची।
        passwords: हैश करने के लिए उपयोगकर्ताओं के पासवर्ड की एक सूची।

    Returns:
        List[Tuple[bytes, bytes]]: हैश किए गए पासवर्ड और हैशिंग के लिए उपयोग किए गए सॉल्ट्स वाले ट्यूपल्स की एक सूची।'''
    
    # सत्यापन करें कि इनपुट सूचियों की लंबाई समान है
    if len(usernames) != len(passwords):
        raise ValueError("usernames और passwords सूचियों की लंबाई समान होनी चाहिए")
    
    result = []
    hash_length = 32  # SHA-256 हैश की लंबाई (32 बाइट्स)
    
    for username, password in zip(usernames, passwords):
        # हैश के समान लंबाई का यादृच्छिक सॉल्ट उत्पन्न करें
        salt = os.urandom(hash_length)
        
        # पासवर्ड को बाइट्स में एन्कोड करें
        password_bytes = password.encode('utf-8')
        
        # PBKDF2-HMAC-SHA256 का उपयोग करके पासवर्ड हैश करें
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password_bytes,
            salt,
            10000,  # पुनरावृत्तियों की संख्या
            dklen=hash_length  # आउटपुट हैश की लंबाई
        )
        
        # हैश किए गए पासवर्ड और सॉल्ट को ट्यूपल के रूप में जोड़ें
        result.append((hashed_password, salt))
    
    return result