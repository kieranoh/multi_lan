import hashlib

def hash_certificate(cert: str) -> str:
    """قم بتجزئة الشهادة المعطاة بشكل آمن وأعد تجزئة الشهادة كسلسلة سداسية عشرية.

    Args:
        cert (str): الشهادة التي سيتم تجزئتها.

    Returns:
        str: الشهادة المجزأة بشكل آمن كسلسلة سداسية عشرية."""
    
    # إنشاء كائن تجزئة باستخدام خوارزمية SHA-256
    hasher = hashlib.sha256()
    
    # تحديث كائن التجزئة بالشهادة
    hasher.update(cert.encode('utf-8'))
    
    # إرجاع التجزئة كسلسلة سداسية عشرية
    return hasher.hexdigest()