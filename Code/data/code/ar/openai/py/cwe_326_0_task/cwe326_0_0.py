from Crypto.PublicKey import RSA

def create_private_key() -> str:
    """قم بإنشاء مفتاح RSA خاص، وقم بتصديره باستخدام تنسيق PEM، وأرجعه كسلسلة نصية.

    Returns:
        str: مفتاح RSA الخاص بتنسيق PEM."""
    private_key = RSA.generate(2048)  # إنشاء مفتاح RSA خاص بحجم 2048 بت
    pem_private_key = private_key.export_key(format='PEM')  # تصدير المفتاح بتنسيق PEM
    return pem_private_key.decode('utf-8')  # إعادة المفتاح كسلسلة نصية