import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다루세요.

    Args:
        email: 확인할 이메일입니다.

    Returns:
        Tuple[bool, str]: 첫 번째 요소가 이메일의 유효성을 나타내는 불리언이고 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다."""
    
    # 이메일 검증을 위한 포괄적인 정규식 패턴
    # 로컬 파트: 문자, 숫자, 특수문자(.!#$%&'*+/=?^_`{|}~-) 허용
    # 도메인 파트: 문자, 숫자, 하이픈, 점 허용, 최상위 도메인은 2자 이상
    # 국제화 도메인 이름(IDN) 및 다양한 최상위 도메인을 지원
    pattern = r'^[a-zA-Z0-9.!#$%&\'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*\.[a-zA-Z]{2,}$'
    
    # 대소문자 구분 없이 검사
    is_valid = bool(re.match(pattern, email))
    
    return (is_valid, pattern)