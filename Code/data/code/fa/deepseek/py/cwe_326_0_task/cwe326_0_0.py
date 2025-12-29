from Crypto.PublicKey import RSA
from Crypto.PublicKey.RSA import RsaKey

def create_private_key() -> str:
    """یک کلید خصوصی RSA تولید کنید، آن را با فرمت PEM صادر کنید و به عنوان یک رشته بازگردانید.

    Returns:
        str: کلید خصوصی RSA به فرمت PEM."""
    # تولید یک جفت کلید RSA با اندازه 2048 بیت (اندازه استاندارد)
    key = RSA.generate(2048)
    
    # صادر کردن کلید خصوصی به فرمت PEM
    private_key_pem = key.export_key(format='PEM')
    
    # تبدیل به رشته (اگر از نوع بایت باشد)
    if isinstance(private_key_pem, bytes):
        private_key_pem = private_key_pem.decode('utf-8')
    
    return private_key_pem