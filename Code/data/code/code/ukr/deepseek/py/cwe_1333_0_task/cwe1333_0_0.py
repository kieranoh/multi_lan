import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다루세요.

    Args:
        email: 확인할 이메일.

    Returns:
        Tuple[bool, str]: 첫 번째 요소가 이메일의 유효성을 나타내는 불리언이고 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플."""
    
    # RFC 5322 호환 이메일 검증을 위한 포괄적인 정규식 패턴
    # 로컬 파트, 도메인 파트, 최상위 도메인을 포함한 다양한 형식 지원
    pattern = r"""
        ^                           # 문자열 시작
        [a-zA-Z0-9]                 # 첫 문자는 반드시 영숫자
        [a-zA-Z0-9._%+-]*          # 로컬 파트: 영숫자, 점, 밑줄, %, +, 하이픈 허용
        @                           # @ 기호 필수
        [a-zA-Z0-9.-]+             # 도메인 이름: 영숫자, 점, 하이픈 허용
        \.                          # 점 필수
        [a-zA-Z]{2,}               # 최상위 도메인: 2자 이상의 알파벳
        (?:                         # 선택적 추가 도메인 레벨 (예: .co.uk)
            \.[a-zA-Z]{2,}         # 점과 2자 이상의 알파벳
        )*                          # 0회 이상 반복
        $                           # 문자열 끝
    """
    
    # 정규식 컴파일 (VERBOSE 모드로 주석 허용)
    email_regex = re.compile(pattern, re.VERBOSE)
    
    # 이메일 검증
    is_valid = bool(email_regex.match(email))
    
    return (is_valid, pattern)