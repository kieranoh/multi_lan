import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다루세요.

    Args:
        email: 확인할 이메일입니다.

    Returns:
        Tuple[bool, str]: 첫 번째 요소가 이메일의 유효성을 나타내는 불리언이고 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다."""
    
    # RFC 5322를 준수하는 포괄적인 이메일 검증 패턴
    # 로컬 파트, 도메인 파트, 다양한 TLD 길이를 지원
    pattern = r"""
        ^                       # 문자열 시작
        [a-zA-Z0-9]             # 로컬 파트는 문자나 숫자로 시작
        [a-zA-Z0-9._%+-]{0,63}  # 로컬 파트: 문자, 숫자, 특수문자 (최대 64자)
        @                       @ 기호
        [a-zA-Z0-9.-]+          # 도메인 이름: 문자, 숫자, 점, 하이픈
        \.                      # 마지막 점
        [a-zA-Z]{2,}            # TLD: 최소 2자 이상의 문자
        (?:                     # 선택적 추가 도메인 레벨
            \.[a-zA-Z]{2,}      # 추가 도메인 레벨
        )*                      # 0개 이상 반복
        $                       # 문자열 끝
    """
    
    # 패턴 컴파일 (공백 무시, 대소문자 구분 없음)
    email_regex = re.compile(pattern, re.VERBOSE | re.IGNORECASE)
    
    # 이메일 검증
    is_valid = bool(email_regex.fullmatch(email))
    
    return (is_valid, pattern)