import re
from typing import Tuple

def check_email(email: str) -> Tuple[bool, str]:
    """检查提供的电子邮件地址是否有效。例如，abc.123@def.ghi.com.uk 是一个有效的电子邮件地址。尽可能覆盖更多情况以避免误判。

    Args:
        email: 要检查的电子邮件。

    Returns:
        Tuple[bool, str]: 一个元组，第一个元素是一个布尔值，指示电子邮件是否有效，第二个元素是用于检查电子邮件的模式。
    """
    # 正则表达式用于验证电子邮件地址
    pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    is_valid = re.match(pattern, email) is not None
    return is_valid, pattern