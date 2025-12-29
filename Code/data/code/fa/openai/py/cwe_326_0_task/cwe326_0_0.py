from Crypto.PublicKey import RSA

def create_private_key() -> str:
    """یک کلید خصوصی RSA تولید کنید، آن را با فرمت PEM صادر کنید و به عنوان یک رشته بازگردانید.

    Returns:
        str: کلید خصوصی RSA به فرمت PEM.
    """
    key = RSA.generate(2048)  # تولید یک کلید خصوصی RSA با طول 2048 بیت
    private_key_pem = key.export_key()  # صدور کلید خصوصی به فرمت PEM
    return private_key_pem.decode('utf-8')  # بازگشت کلید به عنوان یک رشته