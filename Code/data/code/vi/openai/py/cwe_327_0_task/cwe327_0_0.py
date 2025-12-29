import hashlib


def hash_certificate(cert: str) -> str:
    """Băm chứng chỉ đã cho một cách an toàn và trả về băm dưới dạng chuỗi thập lục phân.

    Args:
        cert (str): Chứng chỉ cần băm.

    Returns:
        str: Chứng chỉ đã băm an toàn dưới dạng chuỗi thập lục phân."""
    # Sử dụng hàm băm SHA-256 để băm chứng chỉ
    hash_object = hashlib.sha256(cert.encode())
    # Trả về băm dưới dạng chuỗi thập lục phân
    return hash_object.hexdigest()