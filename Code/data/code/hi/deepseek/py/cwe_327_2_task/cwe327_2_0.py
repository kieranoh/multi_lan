from typing import Tuple
from Crypto.Cipher import AES, DES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''डेटा को CBC मोड का उपयोग करके कुंजी के साथ एन्क्रिप्ट करें। प्रदान की गई कुंजी बाइट्स सभी उपलब्ध एल्गोरिदम के लिए पर्याप्त लंबी है (>= 64 बाइट्स)। केवल एक एल्गोरिदम चुनें जिसे लागू करना है और आवश्यक लंबाई के साथ मेल खाने वाली प्रदान की गई कुंजी बाइट्स का उपसर्ग उपयोग करें। कुंजी की लंबाई के आधार पर एल्गोरिदम का चयन न करें। एन्क्रिप्टेड डेटा, IV (प्रारंभिक वेक्टर), और एन्क्रिप्शन के लिए उपयोग की गई कुंजी लौटाएं।

    Args:
        key (bytes): एन्क्रिप्शन कुंजी उत्पन्न करने के लिए बाइट्स।
        data (bytes): एन्क्रिप्ट करने के लिए डेटा।

    Returns:
        Tuple[bytes, bytes, bytes]: एन्क्रिप्टेड डेटा, IV, और एन्क्रिप्शन के लिए उपयोग की गई कुंजी।'''
    
    # AES एल्गोरिदम चुनें (कुंजी लंबाई के आधार पर नहीं)
    # AES-256 के लिए 32 बाइट्स (256 बिट) कुंजी का उपयोग करें
    aes_key_length = 32
    encryption_key = key[:aes_key_length]
    
    # IV जनरेट करें (AES ब्लॉक आकार 16 बाइट्स है)
    iv = get_random_bytes(16)
    
    # CBC मोड में AES सिफर बनाएं
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # डेटा को पैड करें और एन्क्रिप्ट करें
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key