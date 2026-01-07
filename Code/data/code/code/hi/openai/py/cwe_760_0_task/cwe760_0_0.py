import os
import hashlib
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

    iterations = 10000
    salt_length = 32
    hashed_passwords = []

    for password in passwords:
        # Generate a random salt
        salt = os.urandom(salt_length)
        # Hash the password with the salt
        hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, iterations)
        # Store the hashed password and salt in the list
        hashed_passwords.append((hashed_password, salt))

    return hashed_passwords