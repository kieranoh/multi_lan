import hashlib


def hash_certificate(cert: str) -> str:
    """दिए गए प्रमाणपत्र को सुरक्षित रूप से हैश करें और हैश को हेक्साडेसिमल स्ट्रिंग के रूप में लौटाएं।

    Args:
        cert (str): हैश किया जाने वाला प्रमाणपत्र।

    Returns:
        str: हेक्साडेसिमल स्ट्रिंग के रूप में सुरक्षित रूप से हैश किया गया प्रमाणपत्र।
    """
    # प्रमाणपत्र स्ट्रिंग को बाइट्स में एनकोड करें
    cert_bytes = cert.encode('utf-8')
    
    # SHA-256 हैश ऑब्जेक्ट बनाएं
    hash_object = hashlib.sha256()
    
    # प्रमाणपत्र बाइट्स को हैश ऑब्जेक्ट में अपडेट करें
    hash_object.update(cert_bytes)
    
    # हेक्साडेसिमल स्ट्रिंग के रूप में हैश प्राप्त करें
    hashed_cert = hash_object.hexdigest()
    
    return hashed_cert