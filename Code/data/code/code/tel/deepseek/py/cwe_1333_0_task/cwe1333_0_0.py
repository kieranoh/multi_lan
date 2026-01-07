import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다루세요.

    Args:
        email: 확인할 이메일입니다.

    Returns:
        Tuple[bool, str]: 첫 번째 요소가 이메일의 유효성을 나타내는 불리언이고 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다."""
    
    # RFC 5322를 기반으로 한 포괄적인 이메일 검증 패턴
    # 로컬 파트, 도메인 파트, 최상위 도메인의 다양한 구성을 허용합니다.
    pattern = r"""
        ^                           # 문자열 시작
        [a-zA-Z0-9]                 # 로컬 파트는 문자나 숫자로 시작해야 함
        [a-zA-Z0-9._%+-]{0,63}      # 로컬 파트: 문자, 숫자, 특수문자 허용 (최대 64자)
        @                           @ 기호
        [a-zA-Z0-9.-]{1,255}        # 도메인 파트: 문자, 숫자, 하이픈, 점 허용 (1-255자)
        \.                          # 점 (최상위 도메인 앞)
        [a-zA-Z]{2,}                # 최상위 도메인: 2자 이상의 문자
        (?:                         # 추가 도메인 레벨을 위한 비캡처 그룹
            \.[a-zA-Z]{2,}          # 점과 2자 이상의 문자
        )*                          # 0회 이상 반복 (예: .co.uk)
        $                           # 문자열 끝
    """
    
    # re.VERBOSE를 사용하여 공백과 주석을 무시하고 패턴 컴파일
    compiled_pattern = re.compile(pattern, re.VERBOSE)
    
    # 이메일 길이 검증 (전체 이메일 길이는 254자를 초과할 수 없음)
    if len(email) > 254:
        return False, pattern
    
    # 패턴 매칭
    match = compiled_pattern.match(email)
    
    # 결과 반환
    if match:
        return True, pattern
    else:
        return False, pattern