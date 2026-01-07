import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다루세요.

    Args:
        email: 확인할 이메일.

    Returns:
        Tuple[bool, str]: 첫 번째 요소가 이메일의 유효성을 나타내는 불리언이고 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플."""
    # RFC 5322 호환 이메일 검증을 위한 정규식 패턴
    pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    
    # 추가 검증: 로컬 파트와 도메인 파트의 세부 규칙 적용
    if not isinstance(email, str) or not email:
        return False, pattern
    
    # 기본 패턴 검사
    if not re.match(pattern, email):
        return False, pattern
    
    # 추가 검증 로직
    local_part, domain_part = email.split('@', 1)
    
    # 로컬 파트 검증
    # 1. 로컬 파트는 64자를 초과할 수 없음
    if len(local_part) > 64:
        return False, pattern
    
    # 2. 로컬 파트는 점으로 시작하거나 끝날 수 없음
    if local_part.startswith('.') or local_part.endswith('.'):
        return False, pattern
    
    # 3. 연속된 점은 허용되지 않음
    if '..' in local_part:
        return False, pattern
    
    # 도메인 파트 검증
    # 1. 도메인 파트는 255자를 초과할 수 없음
    if len(domain_part) > 255:
        return False, pattern
    
    # 2. 도메인 파트는 점으로 시작하거나 끝날 수 없음
    if domain_part.startswith('.') or domain_part.endswith('.'):
        return False, pattern
    
    # 3. 연속된 점은 허용되지 않음
    if '..' in domain_part:
        return False, pattern
    
    # 4. 도메인 레이블 검증 (점으로 구분된 각 부분)
    labels = domain_part.split('.')
    for label in labels:
        # 각 레이블은 1-63자 사이여야 함
        if len(label) < 1 or len(label) > 63:
            return False, pattern
        
        # 레이블은 하이픈으로 시작하거나 끝날 수 없음
        if label.startswith('-') or label.endswith('-'):
            return False, pattern
        
        # 레이블은 알파벳, 숫자, 하이픈만 포함할 수 있음
        if not re.match(r'^[a-zA-Z0-9-]+$', label):
            return False, pattern
    
    # 모든 검증 통과
    return True, pattern