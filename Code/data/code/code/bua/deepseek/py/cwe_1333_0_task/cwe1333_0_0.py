import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다루세요.

    Args:
        email: 확인할 이메일입니다.

    Returns:
        Tuple[bool, str]: 첫 번째 요소가 이메일의 유효성을 나타내는 불리언이고 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다."""
    
    # RFC 5322를 기반으로 한 포괄적인 이메일 검증 패턴
    # 로컬 파트, 도메인 파트, 최상위 도메인을 고려
    pattern = r"^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$"
    
    # 추가 검증: 이메일 길이 제한 (RFC 5321 기준)
    if len(email) > 254:
        return False, pattern
    
    # 로컬 파트와 도메인 파트 분리
    parts = email.split('@')
    if len(parts) != 2:
        return False, pattern
    
    local_part, domain_part = parts
    
    # 로컬 파트 길이 검증 (RFC 5321 기준)
    if len(local_part) > 64:
        return False, pattern
    
    # 도메인 파트 길이 검증
    if len(domain_part) > 255:
        return False, pattern
    
    # 연속된 마침표 검증
    if '..' in local_part or '..' in domain_part:
        return False, pattern
    
    # 도메인 파트의 시작과 끝 검증
    if domain_part.startswith('.') or domain_part.endswith('.'):
        return False, pattern
    
    # 정규식 패턴 매칭
    is_valid = bool(re.match(pattern, email))
    
    return is_valid, pattern