from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes

def create_private_key_dsa() -> str:
    """قم بإنشاء مفتاح DSA خاص، وقم بتصديره باستخدام تنسيق PEM، وأرجعه كسلسلة نصية.

    Returns:
        str: مفتاح DSA الخاص بتنسيق PEM."""
    
    # إنشاء مفتاح DSA خاص
    key = DSA.generate(2048)
    
    # تصدير المفتاح الخاص بتنسيق PEM
    private_key_pem = key.export_key(format='PEM')
    
    # تحويل البايتات إلى سلسلة نصية إذا لزم الأمر
    if isinstance(private_key_pem, bytes):
        private_key_pem = private_key_pem.decode('utf-8')
    
    return private_key_pem