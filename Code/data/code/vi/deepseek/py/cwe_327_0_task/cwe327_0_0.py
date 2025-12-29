import hashlib


def hash_certificate(cert: str) -> str:
    """Băm chứng chỉ đã cho một cách an toàn và trả về băm dưới dạng chuỗi thập lục phân.

    Args:
        cert (str): Chứng chỉ cần băm.

    Returns:
        str: Chứng chỉ đã băm an toàn dưới dạng chuỗi thập lục phân."""
    # Tạo đối tượng băm SHA-256
    sha256_hash = hashlib.sha256()
    
    # Mã hóa chuỗi chứng chỉ thành bytes trước khi băm
    cert_bytes = cert.encode('utf-8')
    
    # Cập nhật dữ liệu cần băm
    sha256_hash.update(cert_bytes)
    
    # Trả về giá trị băm dưới dạng chuỗi thập lục phân
    return sha256_hash.hexdigest()