import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다루세요.

    Args:
        email: 확인할 이메일입니다.

    Returns:
        Tuple[bool, str]: 첫 번째 요소가 이메일의 유효성을 나타내는 불리언이고 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다."""
    
    # RFC 5322 호환 이메일 검증 패턴
    # 이 패턴은 다음과 같은 요소를 포함합니다:
    # 1. 로컬 파트: 문자, 숫자, 특수문자(.!#$%&'*+/=?^_`{|}~-) 허용
    # 2. @ 기호
    # 3. 도메인 파트: 문자, 숫자, 하이픈, 점 허용
    # 4. 최상위 도메인: 2자 이상의 문자
    
    # 상세한 패턴 설명:
    # ^ - 문자열 시작
    # [a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+ - 로컬 파트 (하나 이상)
    # @ - @ 기호
    # [a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])? - 도메인 이름 (길이 제한 포함)
    # (?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)* - 서브도메인 (0개 이상)
    # \.[a-zA-Z0-9]{2,} - 최상위 도메인 (2자 이상)
    # $ - 문자열 끝
    
    pattern = r"^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*\.[a-zA-Z0-9]{2,}$"
    
    # 추가 검증: 로컬 파트의 시작과 끝이 점이 아닌지 확인
    if re.match(pattern, email):
        # 로컬 파트 추출
        local_part = email.split('@')[0]
        
        # 로컬 파트가 점으로 시작하거나 끝나지 않는지 확인
        if local_part.startswith('.') or local_part.endswith('.'):
            return False, pattern
        
        # 연속된 점이 없는지 확인
        if '..' in local_part:
            return False, pattern
        
        # 도메인 파트 추출
        domain_part = email.split('@')[1]
        
        # 도메인 파트가 점으로 시작하거나 끝나지 않는지 확인
        if domain_part.startswith('.') or domain_part.endswith('.'):
            return False, pattern
        
        # 도메인 파트에 연속된 점이 없는지 확인
        if '..' in domain_part:
            return False, pattern
        
        # 도메인 파트의 각 레이블(점으로 구분된 부분)이 63자 이하인지 확인
        labels = domain_part.split('.')
        for label in labels:
            if len(label) > 63:
                return False, pattern
        
        # 모든 검증 통과
        return True, pattern
    else:
        return False, pattern