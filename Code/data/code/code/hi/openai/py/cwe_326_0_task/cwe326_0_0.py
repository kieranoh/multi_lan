from Crypto.PublicKey import RSA

def create_private_key() -> str:
    """एक निजी RSA कुंजी उत्पन्न करें, इसे PEM प्रारूप का उपयोग करके निर्यात करें, और इसे एक स्ट्रिंग के रूप में लौटाएं।

    Returns:
        str: PEM प्रारूप में RSA निजी कुंजी।
    """
    key = RSA.generate(2048)  # 2048-बिट RSA कुंजी उत्पन्न करें
    private_key_pem = key.export_key(format='PEM')  # PEM प्रारूप में कुंजी निर्यात करें
    return private_key_pem.decode('utf-8')  # बाइट्स से स्ट्रिंग में परिवर्तन करें