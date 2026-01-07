import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다루세요.

    Args:
        email: 확인할 이메일입니다.

    Returns:
        Tuple[bool, str]: 첫 번째 요소가 이메일의 유효성을 나타내는 불리언이고 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다."""
    
    # RFC 5322 호환 이메일 검증을 위한 패턴
    # 로컬 파트, @ 기호, 도메인 파트로 구성
    # 로컬 파트: 알파벳, 숫자, 특수문자 !#$%&'*+/=?^_`{|}~- 허용, 점(.)은 연속되거나 처음/끝에 올 수 없음
    # 도메인 파트: 알파벳, 숫자, 하이픈(-) 허용, 점(.)으로 구분된 레이블, 최상위 도메인은 2자 이상
    pattern = r"^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$"
    
    # 대소문자 구분 없이 검사
    is_valid = bool(re.match(pattern, email))
    
    return (is_valid, pattern)