import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다루세요.

    Args:
        email: 확인할 이메일.

    Returns:
        Tuple[bool, str]: 첫 번째 요소가 이메일의 유효성을 나타내는 불리언이고 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플."""
    
    # RFC 5322를 준수하는 포괄적인 이메일 검증 패턴
    # 로컬 파트, 도메인 파트, 최상위 도메인을 모두 고려
    pattern = r"""
        ^                           # 문자열 시작
        [a-zA-Z0-9]                 # 첫 문자는 영숫자여야 함
        [a-zA-Z0-9._%+-]{0,63}     # 로컬 파트: 영숫자, 점, 밑줄, %, +, 하이픈 (최대 64자)
        @                           # @ 기호
        [a-zA-Z0-9.-]{1,255}       # 도메인 파트: 영숫자, 점, 하이픈 (1-255자)
        \.                          # 점 (최상위 도메인 구분자)
        [a-zA-Z]{2,}                # 최상위 도메인: 영문자 2자 이상
        (?:                         # 선택적 추가 도메인 레벨 (예: co.uk, ac.kr)
            \.[a-zA-Z]{2,}          # 점과 영문자 2자 이상
        )*                          # 0회 이상 반복
        $                           # 문자열 끝
    """
    
    # 패턴 컴파일 (공백 무시, 대소문자 구분 없음)
    email_regex = re.compile(pattern, re.VERBOSE | re.IGNORECASE)
    
    # 이메일 길이 검증 (전체 길이 최대 254자, 로컬 파트 최대 64자)
    if len(email) > 254:
        return False, pattern
    
    # @ 기호로 분리하여 로컬 파트 길이 검증
    parts = email.split('@')
    if len(parts) != 2:
        return False, pattern
    
    local_part = parts[0]
    if len(local_part) > 64 or len(local_part) == 0:
        return False, pattern
    
    # 연속된 점이나 하이픈 검증
    if '..' in local_part or local_part.startswith('.') or local_part.endswith('.'):
        return False, pattern
    
    # 도메인 파트 검증
    domain_part = parts[1]
    if '..' in domain_part or domain_part.startswith('.') or domain_part.endswith('.'):
        return False, pattern
    
    # 정규식 패턴 매칭
    match = email_regex.fullmatch(email)
    is_valid = bool(match)
    
    return is_valid, pattern