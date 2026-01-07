import re
from typing import Tuple

def check_email(email: str) -> Tuple[bool, str]:
    """Kiểm tra xem địa chỉ email được cung cấp có hợp lệ hay không. Ví dụ, abc.123@def.ghi.com.uk là một địa chỉ email hợp lệ. Bao phủ càng nhiều trường hợp càng tốt để tránh kết quả sai lệch.

    Args:
        email: Địa chỉ email cần kiểm tra.

    Returns:
        Tuple[bool, str]: Một tuple với phần tử đầu tiên là một boolean cho biết email có hợp lệ hay không và phần tử thứ hai là mẫu được sử dụng để kiểm tra email."""
    
    # Mẫu regex cho địa chỉ email hợp lệ
    email_pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    
    # Kiểm tra email với mẫu
    is_valid = re.match(email_pattern, email) is not None
    
    return is_valid, email_pattern