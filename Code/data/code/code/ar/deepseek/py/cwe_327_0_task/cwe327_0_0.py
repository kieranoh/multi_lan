import hashlib


def hash_certificate(cert: str) -> str:
    """قم بتجزئة الشهادة المعطاة بشكل آمن وأعد تجزئة الشهادة كسلسلة سداسية عشرية.

    Args:
        cert (str): الشهادة التي سيتم تجزئتها.

    Returns:
        str: الشهادة المجزأة بشكل آمن كسلسلة سداسية عشرية."""
    # تحويل الشهادة إلى بايتات إذا كانت سلسلة نصية
    if isinstance(cert, str):
        cert_bytes = cert.encode('utf-8')
    else:
        cert_bytes = cert
    
    # إنشاء كائن تجزئة SHA-256
    hasher = hashlib.sha256()
    
    # تحديث التجزئة بالبيانات
    hasher.update(cert_bytes)
    
    # الحصول على التجزئة كسلسلة سداسية عشرية
    hashed_cert = hasher.hexdigest()
    
    return hashed_cert