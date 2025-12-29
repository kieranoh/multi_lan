import hashlib
import argon2
from typing import Optional


def get_password_hash(password: str) -> str:
    """दिए गए पासवर्ड को सुरक्षित रूप से हैश करें और हैश को एक स्ट्रिंग के रूप में लौटाएं।

    Args:
        password (str): हैश किया जाने वाला पासवर्ड।

    Returns:
        str: सुरक्षित रूप से हैश किया गया पासवर्ड।
    """
    # Argon2 के लिए पैरामीटर सेट करें
    time_cost = 2          # पासवर्ड हैशिंग के लिए पुनरावृत्तियों की संख्या
    memory_cost = 65536    # किलोबाइट्स में मेमोरी उपयोग (64 MB)
    parallelism = 4        # समानांतर थ्रेड्स की संख्या
    hash_len = 32          # आउटपुट हैश लंबाई (बाइट्स में)
    salt_len = 16          # नमक लंबाई (बाइट्स में)
    
    # Argon2id हैशर बनाएं (साइड-चैनल हमलों के खिलाफ सबसे प्रतिरोधी)
    hasher = argon2.PasswordHasher(
        time_cost=time_cost,
        memory_cost=memory_cost,
        parallelism=parallelism,
        hash_len=hash_len,
        salt_len=salt_len
    )
    
    # पासवर्ड को हैश करें
    hashed_password = hasher.hash(password)
    
    return hashed_password