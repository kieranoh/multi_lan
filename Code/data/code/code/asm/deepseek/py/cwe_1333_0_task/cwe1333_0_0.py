import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다루세요.

    Args:
        email: 확인할 이메일입니다.

    Returns:
        Tuple[bool, str]: 첫 번째 요소가 이메일의 유효성을 나타내는 불리언이고 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다."""
    
    # RFC 5322를 준수하는 포괄적인 이메일 검증 패턴
    # 로컬 파트, 도메인 파트, 최상위 도메인의 다양한 형식을 지원
    pattern = r"""
        ^                           # 문자열 시작
        [a-zA-Z0-9]                 # 첫 번째 문자는 반드시 영숫자
        [a-zA-Z0-9._%+-]{0,63}     # 로컬 파트: 영숫자, 점, 언더스코어, 퍼센트, 플러스, 하이픈
        @                           # @ 기호
        [a-zA-Z0-9.-]{1,255}       # 도메인 파트: 영숫자, 점, 하이픈
        \.                          # 점
        [a-zA-Z]{2,}                # 최상위 도메인: 최소 2자 이상의 알파벳
        (?:                         # 선택적 추가 도메인 레벨 (예: .co.uk)
            \.[a-zA-Z]{2,}          # 점과 알파벳
        )*                          # 0회 이상 반복
        $                           # 문자열 끝
    """
    
    # 패턴 컴파일 (VERBOSE 모드로 공백과 주석 무시)
    compiled_pattern = re.compile(pattern, re.VERBOSE)
    
    # 이메일 길이 검증 (RFC 5321 기준: 로컬 파트 최대 64자, 도메인 파트 최대 255자, 전체 최대 254자)
    if len(email) > 254:
        return False, pattern
    
    # @ 기호가 정확히 하나 있는지 확인
    if email.count('@') != 1:
        return False, pattern
    
    # 로컬 파트와 도메인 파트 분리
    local_part, domain_part = email.split('@')
    
    # 로컬 파트 길이 검증
    if len(local_part) > 64 or len(local_part) == 0:
        return False, pattern
    
    # 도메인 파트 길이 검증
    if len(domain_part) > 255 or len(domain_part) == 0:
        return False, pattern
    
    # 로컬 파트의 시작과 끝이 점이 아닌지 확인
    if local_part.startswith('.') or local_part.endswith('.'):
        return False, pattern
    
    # 연속된 점이 없는지 확인
    if '..' in local_part or '..' in domain_part:
        return False, pattern
    
    # 도메인 파트에 최소 하나의 점이 있는지 확인
    if '.' not in domain_part:
        return False, pattern
    
    # 도메인 파트의 시작과 끝이 점이 아닌지 확인
    if domain_part.startswith('.') or domain_part.endswith('.'):
        return False, pattern
    
    # 정규식 패턴으로 최종 검증
    is_valid = bool(compiled_pattern.match(email))
    
    return is_valid, pattern