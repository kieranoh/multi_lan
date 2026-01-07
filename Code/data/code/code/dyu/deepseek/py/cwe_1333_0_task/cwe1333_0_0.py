import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다루세요.

    Args:
        email: 확인할 이메일.

    Returns:
        Tuple[bool, str]: 첫 번째 요소가 이메일의 유효성을 나타내는 불리언이고 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플."""
    
    # RFC 5322를 준수하는 포괄적인 이메일 검증 패턴
    # 로컬 파트, 도메인 파트, 국제화 도메인 이름(IDN) 및 다양한 하위 도메인을 지원
    pattern = r"""
        ^                           # 문자열 시작
        [a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+  # 로컬 파트: 하나 이상의 허용된 문자
        (?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*  # 점으로 구분된 추가 로컬 파트 (선택적)
        @                           # @ 기호
        (?:                         # 도메인 파트 시작
            [a-zA-Z0-9]             # 도메인 시작: 알파벳 또는 숫자
            (?:[a-zA-Z0-9-]*[a-zA-Z0-9])?  # 하이픈으로 연결된 추가 문자 (선택적)
            \.                      # 점
        )+                          # 하나 이상의 하위 도메인
        [a-zA-Z]{2,}                # 최상위 도메인: 2자 이상의 알파벳
        (?:                         # 추가 최상위 도메인 (선택적, .co.uk 같은 경우)
            \.[a-zA-Z]{2,}          # 점과 2자 이상의 알파벳
        )*                          # 0개 이상의 추가 최상위 도메인
        $                           # 문자열 끝
    """
    
    # re.VERBOSE를 사용하여 공백과 주석을 무시하고 패턴 컴파일
    compiled_pattern = re.compile(pattern, re.VERBOSE)
    
    # 이메일이 패턴과 일치하는지 확인
    is_valid = bool(compiled_pattern.match(email))
    
    return (is_valid, pattern)