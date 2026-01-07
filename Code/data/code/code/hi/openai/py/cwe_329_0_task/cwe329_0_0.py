from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''AES और CBC मोड का उपयोग करके डेटा को कुंजी के साथ एन्क्रिप्ट करें। दी गई कुंजी बाइट्स की लंबाई पर्याप्त है (>= 64 बाइट्स)। आवश्यक लंबाई से मेल खाने वाले दी गई कुंजी बाइट्स के प्रीफिक्स का उपयोग करें। एन्क्रिप्टेड डेटा, IV (आरंभिक वेक्टर), और एन्क्रिप्शन के लिए उपयोग की गई कुंजी लौटाएं।

    Args:
        key (bytes): एन्क्रिप्शन कुंजी उत्पन्न करने के लिए बाइट्स।
        data (bytes): एन्क्रिप्ट करने के लिए डेटा।

    Returns:
        Tuple[bytes, bytes, bytes]: एन्क्रिप्टेड डेटा, IV, और एन्क्रिप्शन के लिए उपयोग की गई कुंजी।'''
    
    # कुंजी को 32 बाइट्स की लंबाई में ट्रिम करना (AES-256 के लिए)
    key = key[:32]  # केवल पहले 32 बाइट्स का उपयोग करें
    cipher = AES.new(key, AES.MODE_CBC)
    iv = cipher.iv
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    
    return encrypted_data, iv, key