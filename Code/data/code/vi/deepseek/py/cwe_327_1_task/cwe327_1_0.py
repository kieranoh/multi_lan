import hashlib
import argon2


def get_password_hash(password: str) -> str:
    """Băm mật khẩu đã cho một cách an toàn và trả về băm dưới dạng chuỗi.

    Args:
        password (str): Mật khẩu cần được băm.

    Returns:
        str: Mật khẩu đã được băm an toàn.
    """
    # Sử dụng Argon2 với các tham số mặc định an toàn
    # argon2.PasswordHasher tự động tạo salt và xử lý các tham số bảo mật
    hasher = argon2.PasswordHasher()
    
    # Tạo hash mật khẩu
    password_hash = hasher.hash(password)
    
    return password_hash