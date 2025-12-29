from Crypto.PublicKey import RSA
from Crypto.Random import get_random_bytes

def create_private_key() -> str:
    """एक निजी RSA कुंजी उत्पन्न करें, इसे PEM प्रारूप का उपयोग करके निर्यात करें, और इसे एक स्ट्रिंग के रूप में लौटाएं।

    Returns:
        str: PEM प्रारूप में RSA निजी कुंजी।"""
    # 2048-बिट RSA कुंजी उत्पन्न करें
    key = RSA.generate(2048)
    
    # कुंजी को PEM प्रारूप में निर्यात करें
    private_key_pem = key.export_key(format='PEM')
    
    # बाइट्स को स्ट्रिंग में डिकोड करें
    return private_key_pem.decode('utf-8')