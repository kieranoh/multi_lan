import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다루십시오.

    Args:
        email: 확인할 이메일.

    Returns:
        Tuple[bool, str]: 첫 번째 요소는 이메일이 유효한지 나타내는 불리언이고, 두 번째 요소는 이메일을 확인하는 데 사용된 패턴입니다."""
    
    # RFC 5322 호환 이메일 검증 패턴
    # 이 패턴은 다음과 같은 이메일 형식을 지원합니다:
    # - 로컬 파트: 문자, 숫자, 특수문자(. ! # $ % & ' * + - / = ? ^ _ ` { | } ~) 허용
    # - 도메인 파트: 하이픈을 포함한 알파벳 숫자, 점으로 구분된 다중 레벨 도메인
    # - 국제화 도메인 이름(IDN) 지원을 위한 유니코드 문자
    # - 최상위 도메인(TLD)은 최소 2자 이상
    pattern = r'^[a-zA-Z0-9!#$%&\'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&\'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$'
    
    # 추가적으로 유니코드 문자를 포함한 이메일 주소를 지원하는 패턴
    # 이 패턴은 국제화 이메일 주소(IETF RFC 6531)를 지원합니다
    unicode_pattern = r'^[a-zA-Z0-9\u0080-\uFFFF!#$%&\'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9\u0080-\uFFFF!#$%&\'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9\u0080-\uFFFF](?:[a-zA-Z0-9\u0080-\uFFFF-]*[a-zA-Z0-9\u0080-\uFFFF])?\.)+[a-zA-Z\u0080-\uFFFF]{2,}$'
    
    # 먼저 기본 ASCII 패턴으로 검증 시도
    if re.match(pattern, email):
        return True, pattern
    
    # ASCII 패턴에 실패하면 유니코드 패턴으로 검증 시도
    if re.match(unicode_pattern, email):
        return True, unicode_pattern
    
    # 두 패턴 모두 실패하면 유효하지 않은 이메일
    return False, pattern