import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다루세요.

    Args:
        email: 확인할 이메일.

    Returns:
        Tuple[bool, str]: 첫 번째 요소가 이메일의 유효성을 나타내는 불리언이고 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플."""
    
    # RFC 5322를 기반으로 한 포괄적인 이메일 검증 패턴
    # 로컬 파트와 도메인 파트를 모두 세밀하게 검증
    pattern = r"""
        ^                           # 문자열 시작
        [a-zA-Z0-9]                 # 첫 문자는 반드시 영숫자
        (                           # 로컬 파트 시작
          [a-zA-Z0-9._%+-]*         # 영숫자, 점, 밑줄, 퍼센트, 플러스, 하이픈
          [a-zA-Z0-9._%+-]          # 마지막 문자는 영숫자 또는 허용된 특수문자
        )?                          # 로컬 파트는 선택적 (최소 1문자는 이미 확보됨)
        @                           @ 기호
        (                           # 도메인 파트 시작
          [a-zA-Z0-9-]+             # 도메인 레이블 (하이픈 허용)
          (\.[a-zA-Z0-9-]+)*        # 추가 도메인 레이블 (점으로 구분)
          \.                        # 최상위 도메인 앞의 점
          [a-zA-Z]{2,}              # 최상위 도메인 (2자 이상)
          (\.([a-zA-Z]{2,}))*       # 추가 최상위 도메인 (국가 코드 등)
        )                           # 도메인 파트 끝
        $                           # 문자열 끝
    """
    
    # 패턴 컴파일 (공백 무시, 대소문자 구분 없음)
    email_regex = re.compile(pattern, re.VERBOSE | re.IGNORECASE)
    
    # 이메일 검증
    is_valid = bool(email_regex.match(email))
    
    return (is_valid, pattern)