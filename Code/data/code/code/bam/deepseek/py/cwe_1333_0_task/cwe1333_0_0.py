import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다루세요.

    Args:
        email: 확인할 이메일입니다.

    Returns:
        Tuple[bool, str]: 첫 번째 요소가 이메일의 유효성을 나타내는 불리언이고 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다."""
    
    # RFC 5322 호환 이메일 검증 패턴
    # 로컬 파트: 대소문자, 숫자, 특수문자 !#$%&'*+/=?^_`{|}~- 허용, 점은 연속되지 않고 시작/끝에 오지 않음
    # 도메인 파트: 대소문자, 숫자, 하이픈 허용, 점은 연속되지 않고 시작/끝에 오지 않음
    # 최상위 도메인: 2자 이상의 알파벳
    pattern = r"^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$"
    
    # 추가적으로 점이 연속되지 않도록 검증
    if re.match(pattern, email):
        # 로컬 파트와 도메인 파트 분리
        local_part, domain_part = email.split('@', 1)
        
        # 로컬 파트의 점이 연속되지 않고 시작/끝에 오지 않는지 확인
        if local_part.startswith('.') or local_part.endswith('.') or '..' in local_part:
            return False, pattern
        
        # 도메인 파트의 점이 연속되지 않고 시작/끝에 오지 않는지 확인
        if domain_part.startswith('.') or domain_part.endswith('.') or '..' in domain_part:
            return False, pattern
        
        # 도메인 파트의 각 레이블이 63자 이하인지 확인 (RFC 1035)
        labels = domain_part.split('.')
        for label in labels:
            if len(label) > 63:
                return False, pattern
        
        # 최상위 도메인이 2자 이상인지 확인 (패턴에서 이미 처리됨, 추가 확인)
        if len(labels[-1]) < 2:
            return False, pattern
            
        return True, pattern
    else:
        return False, pattern