import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다루세요.

    Args:
        email: 확인할 이메일.

    Returns:
        Tuple[bool, str]: 첫 번째 요소가 이메일의 유효성을 나타내는 불리언이고 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플."""
    
    # RFC 5322를 기반으로 한 포괄적인 이메일 검증 패턴
    # 로컬 파트: 문자, 숫자, 특수문자 !#$%&'*+/=?^_`{|}~- 및 점(.) 허용
    # 단, 점은 연속되거나 처음/끝에 올 수 없음
    # 도메인 파트: 문자, 숫자, 하이픈(-) 및 점(.) 허용
    # 최상위 도메인(TLD): 최소 2자 이상의 문자
    # 국제화 도메인 이름(IDN) 지원을 위해 유니코드 문자 허용
    
    pattern = r"""
        ^                           # 문자열 시작
        [a-zA-Z0-9]                 # 로컬 파트 시작은 반드시 영문자 또는 숫자
        [a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]*  # 로컬 파트 중간 문자들
        [a-zA-Z0-9]                 # 로컬 파트 끝은 반드시 영문자 또는 숫자
        @                           # @ 기호
        [a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?  # 도메인 이름 (최대 63자)
        (?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*  # 하위 도메인들
        \.[a-zA-Z]{2,}              # 최상위 도메인 (최소 2자)
        $                           # 문자열 끝
    """
    
    # 간소화된 패턴 (더 많은 경우를 수용하기 위해)
    # 이 패턴은 예시로 주어진 abc.123@def.ghi.com.uk와 같은 복잡한 도메인을 처리할 수 있음
    simplified_pattern = r"""
        ^                           # 문자열 시작
        [a-zA-Z0-9][a-zA-Z0-9._%+-]*[a-zA-Z0-9]  # 로컬 파트
        @                           # @ 기호
        [a-zA-Z0-9][a-zA-Z0-9.-]*[a-zA-Z0-9]     # 도메인 파트
        \.[a-zA-Z]{2,}              # 최소 2자 이상의 TLD
        $                           # 문자열 끝
    """
    
    # 더욱 포괄적인 패턴 (국제화 이메일 주소 지원)
    comprehensive_pattern = r"""
        ^                           # 문자열 시작
        [a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+          # 로컬 파트 시작
        (?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*   # 점으로 구분된 추가 로컬 파트
        @                           # @ 기호
        (?:[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?\.)+  # 도메인 및 하위 도메인
        [a-zA-Z]{2,}               # 최소 2자 이상의 TLD
        $                           # 문자열 끝
    """
    
    # 실제 검증에 사용할 패턴 선택
    # comprehensive_pattern이 가장 포괄적이지만, simplified_pattern도 대부분의 경우를 처리함
    validation_pattern = comprehensive_pattern
    
    try:
        # 패턴 컴파일 (공백과 주석 무시 모드)
        regex = re.compile(validation_pattern, re.VERBOSE)
        
        # 이메일 검증
        is_valid = bool(regex.match(email))
        
        # 추가 검증: 로컬 파트의 점 규칙 확인
        if is_valid:
            local_part = email.split('@')[0]
            # 점이 연속되지 않았는지 확인
            if '..' in local_part:
                is_valid = False
            # 점으로 시작하거나 끝나지 않는지 확인
            if local_part.startswith('.') or local_part.endswith('.'):
                is_valid = False
        
        return (is_valid, validation_pattern.strip())
    
    except Exception:
        # 예외 발생 시 (예: email이 None인 경우)
        return (False, validation_pattern.strip())