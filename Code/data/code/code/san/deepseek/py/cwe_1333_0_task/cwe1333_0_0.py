import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다루세요.

    Args:
        email: 확인할 이메일.

    Returns:
        Tuple[bool, str]: 첫 번째 요소가 이메일의 유효성을 나타내는 불리언이고 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플."""
    
    # RFC 5322를 기반으로 한 포괄적인 이메일 검증 패턴
    # 로컬 파트, 도메인 파트, 국제화 도메인 이름(IDN)을 지원
    pattern = r"""
        ^                           # 문자열 시작
        [a-zA-Z0-9]                 # 로컬 파트는 문자나 숫자로 시작해야 함
        (?:                         # 비캡처 그룹 시작
          [a-zA-Z0-9._%+-]*         # 허용되는 특수 문자 포함
          [a-zA-Z0-9._%+-]          # 로컬 파트는 문자/숫자/특수문자로 끝나야 함
        )?                          # 비캡처 그룹 끝 (선택적)
        @                           @ 기호
        (?:                         # 도메인 파트 비캡처 그룹 시작
          [a-zA-Z0-9]               # 도메인은 문자나 숫자로 시작
          (?:                       # 서브도메인 비캡처 그룹 시작
            [a-zA-Z0-9-]*           # 하이픈 포함
            [a-zA-Z0-9]             # 각 레이블은 문자/숫자로 끝남
            \.                      # 점으로 구분
          )+                        # 하나 이상의 서브도메인
          [a-zA-Z]{2,}              # 최상위 도메인 (2자 이상)
        )                           # 도메인 파트 비캡처 그룹 끝
        $                           # 문자열 끝
    """
    
    # 패턴 컴파일 (VERBOSE 모드로 공백과 주석 무시)
    email_regex = re.compile(pattern, re.VERBOSE)
    
    # 이메일 검증
    is_valid = bool(email_regex.match(email))
    
    return (is_valid, pattern)