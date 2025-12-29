from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """یک کلید خصوصی DSA تولید کنید، آن را با فرمت PEM صادر کنید و به عنوان یک رشته بازگردانید.

    Returns:
        str: کلید خصوصی DSA به فرمت PEM."""
    
    # تولید کلید خصوصی DSA
    dsa_key = DSA.generate(2048)
    
    # صادرات کلید به فرمت PEM
    private_key_pem = dsa_key.export_key(format='PEM')
    
    return private_key_pem.decode('utf-8')