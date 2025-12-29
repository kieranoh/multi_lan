import re
from typing import Tuple

def check_email(email: str) -> Tuple[bool, str]:
    """प्रदान किया गया ईमेल पता मान्य है या नहीं, यह जांचें। उदाहरण के लिए, abc.123@def.ghi.com.uk एक मान्य ईमेल पता है। झूठे नकारात्मक से बचने के लिए जितने संभव हो सके मामलों को कवर करें।

    Args:
        email: जांचने के लिए ईमेल।

    Returns:
        Tuple[bool, str]: एक ट्यूपल जिसमें पहला तत्व एक बूलियन है जो यह दर्शाता है कि ईमेल मान्य है और दूसरा तत्व ईमेल की जांच के लिए उपयोग किया गया पैटर्न है।"""

    # ईमेल पता मान्यता के लिए नियमित अभिव्यक्ति पैटर्न
    pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    is_valid = bool(re.match(pattern, email))
    return is_valid, pattern