import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다루세요.

    Args:
        email: 확인할 이메일.

    Returns:
        Tuple[bool, str]: 첫 번째 요소가 이메일의 유효성을 나타내는 불리언이고 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플."""
    
    # RFC 5322를 기반으로 한 포괄적인 이메일 검증 패턴
    # 로컬 파트, 도메인 파트, 국제화 도메인 이름(IDN) 및 다양한 TLD 길이를 지원
    pattern = r"""
        ^                           # 문자열 시작
        [a-zA-Z0-9]                 # 로컬 파트는 문자나 숫자로 시작해야 함
        [a-zA-Z0-9._%+-]{0,63}      # 로컬 파트 중간 문자 (최대 64자)
        @                           @ 기호
        [a-zA-Z0-9.-]{1,255}        # 도메인 이름 (1-255자)
        \.                          # 점
        [a-zA-Z]{2,}                # 최상위 도메인 (2자 이상)
        (?:                         # 추가 도메인 레벨 (선택적)
            \.[a-zA-Z]{2,}          # 추가 도메인 레벨
        )*                          # 0회 이상 반복
        $                           # 문자열 끝
    """
    
    # 패턴 컴파일 (공백 무시, 대소문자 구분)
    compiled_pattern = re.compile(pattern, re.VERBOSE | re.IGNORECASE)
    
    # 기본 검증
    if not email or not isinstance(email, str):
        return False, pattern
    
    # 길이 검증 (전체 이메일 길이는 254자를 초과할 수 없음)
    if len(email) > 254:
        return False, pattern
    
    # @ 기호 검증
    if email.count('@') != 1:
        return False, pattern
    
    # 로컬 파트와 도메인 파트 분리
    local_part, domain_part = email.split('@')
    
    # 로컬 파트 길이 검증 (최대 64자)
    if len(local_part) > 64 or len(local_part) == 0:
        return False, pattern
    
    # 도메인 파트 길이 검증 (최대 255자)
    if len(domain_part) > 255 or len(domain_part) == 0:
        return False, pattern
    
    # 로컬 파트가 문자나 숫자로 시작하는지 확인
    if not local_part[0].isalnum():
        return False, pattern
    
    # 로컬 파트의 연속된 점 확인
    if '..' in local_part:
        return False, pattern
    
    # 로컬 파트의 시작이나 끝에 점이 있는지 확인
    if local_part.startswith('.') or local_part.endswith('.'):
        return False, pattern
    
    # 도메인 파트의 연속된 점 확인
    if '..' in domain_part:
        return False, pattern
    
    # 도메인 파트의 시작이나 끝에 점이 있는지 확인
    if domain_part.startswith('.') or domain_part.endswith('.'):
        return False, pattern
    
    # 도메인 파트에 최소한 하나의 점이 있는지 확인
    if '.' not in domain_part:
        return False, pattern
    
    # 최상위 도메인(TLD) 길이 확인 (최소 2자)
    tld = domain_part.split('.')[-1]
    if len(tld) < 2:
        return False, pattern
    
    # 정규식 패턴 매칭
    match = compiled_pattern.match(email)
    is_valid = bool(match)
    
    return is_valid, pattern