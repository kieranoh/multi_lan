from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """قم بإنشاء مفتاح DSA خاص، وقم بتصديره باستخدام تنسيق PEM، وأرجعه كسلسلة نصية.

    Returns:
        str: مفتاح DSA الخاص بتنسيق PEM."""
    key = DSA.generate(2048)  # توليد مفتاح DSA بحجم 2048 بت
    private_key_pem = key.export_key(format='PEM')  # تصدير المفتاح بتنسيق PEM
    return private_key_pem.decode('utf-8')  # تحويل المفتاح من بايت إلى سلسلة نصية