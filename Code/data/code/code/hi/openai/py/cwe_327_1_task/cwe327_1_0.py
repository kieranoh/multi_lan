import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """दिए गए पासवर्ड को सुरक्षित रूप से हैश करें और हैश को एक स्ट्रिंग के रूप में लौटाएं।

    Args:
        password (str): हैश किया जाने वाला पासवर्ड।

    Returns:
        str: सुरक्षित रूप से हैश किया गया पासवर्ड।
    """
    # Initialize the Argon2 password hasher
    hasher = argon2.PasswordHasher()
    
    # Hash the password
    hashed_password = hasher.hash(password)
    
    return hashed_password