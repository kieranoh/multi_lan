import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다룹니다.

    Args:
        email: 확인할 이메일입니다.

    Returns:
        Tuple[bool, str]: 첫 번째 요소가 이메일의 유효성을 나타내는 불리언이고 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다."""
    
    # RFC 5322 호환 이메일 검증을 위한 패턴
    # 로컬 파트, 도메인 파트를 정확히 구분하며 다양한 유효한 형식을 지원
    pattern = r'^[a-zA-Z0-9!#$%&\'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&\'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$'
    
    # 패턴 컴파일
    email_regex = re.compile(pattern)
    
    # 이메일 검증
    is_valid = bool(email_regex.fullmatch(email))
    
    return (is_valid, pattern)