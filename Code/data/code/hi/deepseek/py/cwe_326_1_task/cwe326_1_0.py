from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes

def create_private_key_dsa() -> str:
    """एक निजी DSA कुंजी उत्पन्न करें, इसे PEM प्रारूप का उपयोग करके निर्यात करें, और इसे एक स्ट्रिंग के रूप में लौटाएं।

    Returns:
        str: PEM प्रारूप में DSA निजी कुंजी।"""
    # 1024-बिट DSA कुंजी उत्पन्न करें
    key = DSA.generate(1024)
    
    # कुंजी को PEM प्रारूप में निर्यात करें
    private_key_pem = key.export_key(format='PEM')
    
    # बाइट्स को स्ट्रिंग में डिकोड करें
    return private_key_pem.decode('utf-8')