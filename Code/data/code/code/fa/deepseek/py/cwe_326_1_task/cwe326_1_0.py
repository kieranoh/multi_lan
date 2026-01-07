from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes

def create_private_key_dsa() -> str:
    """یک کلید خصوصی DSA تولید کنید، آن را با فرمت PEM صادر کنید و به عنوان یک رشته بازگردانید.

    Returns:
        str: کلید خصوصی DSA به فرمت PEM."""
    # تولید کلید DSA با اندازه 2048 بیت
    key = DSA.generate(2048)
    
    # صادر کردن کلید خصوصی در فرمت PEM
    private_key_pem = key.export_key(format='PEM')
    
    # تبدیل به رشته (اگر از قبل رشته نیست)
    if isinstance(private_key_pem, bytes):
        private_key_pem = private_key_pem.decode('utf-8')
    
    return private_key_pem