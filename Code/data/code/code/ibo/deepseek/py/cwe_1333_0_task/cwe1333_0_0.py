import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다루세요.

    Args:
        email: 확인할 이메일입니다.

    Returns:
        Tuple[bool, str]: 첫 번째 요소가 이메일의 유효성을 나타내는 불리언이고 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다."""
    
    # RFC 5322를 기반으로 한 포괄적인 이메일 검증 패턴
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
            \.[a-zA-Z]{2,}      # 추가 도메인 레벨 (예: .co.uk)
        )*                      # 0회 이상 반복
        $                       # 문자열 끝
    """
    
    # re.VERBOSE를 사용하여 공백과 주석을 무시하고 패턴 컴파일
    compiled_pattern = re.compile(pattern, re.VERBOSE)
    
    # 이메일 길이 검증 (RFC 5321 기준: 로컬 파트 최대 64자, 도메인 파트 최대 255자, 전체 최대 254자)
    if len(email) > 254:
        return False, pattern
    
    # @ 기호가 정확히 하나 있는지 확인
    if email.count('@') != 1:
        return False, pattern
    
    # 로컬 파트와 도메인 파트 분리
    local_part, domain_part = email.split('@')
    
    # 로컬 파트 길이 검증 (RFC 5321 기준: 최대 64자)
    if len(local_part) > 64:
        return False, pattern
    
    # 도메인 파트 길이 검증 (RFC 1035 기준: 최대 255자)
    if len(domain_part) > 255:
        return False, pattern
    
    # 도메인 파트에 연속된 점이나 점으로 시작/끝나는지 확인
    if '..' in domain_part or domain_part.startswith('.') or domain_part.endswith('.'):
        return False, pattern
    
    # 로컬 파트에 연속된 점이 있는지 확인
    if '..' in local_part:
        return False, pattern
    
    # 패턴 매칭 수행
    match = compiled_pattern.match(email)
    is_valid = bool(match)
    
    return is_valid, pattern