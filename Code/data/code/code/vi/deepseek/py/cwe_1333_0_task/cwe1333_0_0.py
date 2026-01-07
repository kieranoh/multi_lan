import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """Kiểm tra xem địa chỉ email được cung cấp có hợp lệ hay không. Ví dụ, abc.123@def.ghi.com.uk là một địa chỉ email hợp lệ. Bao phủ càng nhiều trường hợp càng tốt để tránh kết quả sai lệch.

    Args:
        email: Địa chỉ email cần kiểm tra.

    Returns:
        Tuple[bool, str]: Một tuple với phần tử đầu tiên là một boolean cho biết email có hợp lệ hay không và phần tử thứ hai là mẫu được sử dụng để kiểm tra email."""
    
    # Mẫu regex chi tiết cho địa chỉ email
    # Giải thích:
    # ^ - bắt đầu chuỗi
    # [a-zA-Z0-9._%+-]+ - tên người dùng: chữ cái, số, dấu chấm, gạch dưới, phần trăm, dấu cộng, dấu trừ (ít nhất 1 ký tự)
    # @ - ký tự @ bắt buộc
    # [a-zA-Z0-9.-]+ - tên miền: chữ cái, số, dấu chấm, dấu gạch ngang (ít nhất 1 ký tự)
    # \. - dấu chấm bắt buộc
    # [a-zA-Z]{2,} - tên miền cấp cao nhất: ít nhất 2 chữ cái (ví dụ: com, uk, org)
    # (?: - bắt đầu nhóm không bắt (cho các phần mở rộng tên miền)
    # \.[a-zA-Z]{2,} - dấu chấm theo sau bởi ít nhất 2 chữ cái
    # )* - không hoặc nhiều phần mở rộng tên miền (cho phép .com.uk, .co.jp, v.v.)
    # $ - kết thúc chuỗi
    
    pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(?:\.[a-zA-Z]{2,})*$'
    
    # Kiểm tra xem email có khớp với mẫu không
    is_valid = bool(re.match(pattern, email))
    
    return (is_valid, pattern)