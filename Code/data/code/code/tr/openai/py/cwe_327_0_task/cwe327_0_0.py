import hashlib


def hash_certificate(cert: str) -> str:
    """Verilen sertifikayı güvenli bir şekilde hash'leyin ve hash'i onaltılık bir dize olarak döndürün.

    Args:
        cert (str): Hash'lenecek sertifika.

    Returns:
        str: Güvenli bir şekilde hash'lenmiş sertifika, onaltılık bir dize olarak."""
    # SHA-256 algoritmasını kullanarak sertifikayı hash'le
    sha256_hash = hashlib.sha256()
    sha256_hash.update(cert.encode('utf-8'))
    # Hash değerini onaltılık dize olarak döndür
    return sha256_hash.hexdigest()