from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """एक निजी DSA कुंजी उत्पन्न करें, इसे PEM प्रारूप का उपयोग करके निर्यात करें, और इसे एक स्ट्रिंग के रूप में लौटाएं।

    Returns:
        str: PEM प्रारूप में DSA निजी कुंजी।
    """
    private_key = DSA.generate(2048)  # 2048-बिट DSA कुंजी उत्पन्न करें
    return private_key.export_key(format='PEM').decode('utf-8')  # PEM प्रारूप में कुंजी निर्यात करें और स्ट्रिंग के रूप में लौटाएं