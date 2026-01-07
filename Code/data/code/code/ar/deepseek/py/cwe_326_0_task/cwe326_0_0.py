from Crypto.PublicKey import RSA
from Crypto.PublicKey.RSA import RsaKey

def create_private_key() -> str:
    """قم بإنشاء مفتاح RSA خاص، وقم بتصديره باستخدام تنسيق PEM، وأرجعه كسلسلة نصية.

    Returns:
        str: مفتاح RSA الخاص بتنسيق PEM."""
    # إنشاء مفتاح RSA خاص بحجم 2048 بت (الحجم القياسي الآمن)
    key = RSA.generate(2048)
    
    # تصدير المفتاح الخاص بتنسيق PEM
    private_key_pem = key.export_key(format='PEM')
    
    # تحويل البايتات إلى سلسلة نصية
    return private_key_pem.decode('utf-8')