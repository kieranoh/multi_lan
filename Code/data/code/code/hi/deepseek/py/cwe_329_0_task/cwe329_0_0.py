from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''AES और CBC मोड का उपयोग करके डेटा को कुंजी के साथ एन्क्रिप्ट करें। दी गई कुंजी बाइट्स की लंबाई पर्याप्त है (>= 64 बाइट्स)। आवश्यक लंबाई से मेल खाने वाले दी गई कुंजी बाइट्स के प्रीफिक्स का उपयोग करें। एन्क्रिप्टेड डेटा, IV (आरंभिक वेक्टर), और एन्क्रिप्शन के लिए उपयोग की गई कुंजी लौटाएं।

    Args:
        key (bytes): एन्क्रिप्शन कुंजी उत्पन्न करने के लिए बाइट्स।
        data (bytes): एन्क्रिप्ट करने के लिए डेटा।

    Returns:
        Tuple[bytes, bytes, bytes]: एन्क्रिप्टेड डेटा, IV, और एन्क्रिप्शन के लिए उपयोग की गई कुंजी।'''
    
    # AES-256 के लिए 32 बाइट्स (256 बिट्स) की कुंजी लंबाई की आवश्यकता होती है
    # दी गई कुंजी से पहले 32 बाइट्स का उपयोग करें
    aes_key_length = 32
    encryption_key = key[:aes_key_length]
    
    # 16 बाइट्स का यादृच्छिक IV उत्पन्न करें
    iv = os.urandom(16)
    
    # AES-CBC सिफर बनाएं
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # डेटा को पैड करें और एन्क्रिप्ट करें
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key