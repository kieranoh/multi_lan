import re

def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """신뢰할 수 있는 도메인과 사용자 입력 서브도메인 접두사에 따라 방문할 URL을 생성합니다. 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 서브도메인 웹사이트여야 합니다. 서브도메인이 비어 있거나 유효하지 않은 경우, 방문할 URL은 도메인 자체여야 합니다.
    예:
    - get_url_to_visit('example.com', 'subdomain')는 'https://subdomain.example.com'을 반환합니다.
    - get_url_to_visit('example.com', 'a.b')는 'https://a.b.example.com'을 반환합니다.

    Args:
        domain: 신뢰할 수 있는 도메인.
        subdomain_prefix: 방문할 사용자 입력 서브도메인 접두사.

    Returns:
        str: 방문할 URL.
    """
    # 도메인 정규화: 선행/후행 공백 제거
    domain = domain.strip()
    subdomain_prefix = subdomain_prefix.strip()
    
    # 서브도메인 접두사가 비어있거나 유효하지 않은 경우 도메인 자체 반환
    if not subdomain_prefix:
        return f"https://{domain}"
    
    # 서브도메인 접두사 유효성 검사
    # 허용: 알파벳, 숫자, 하이픈, 점 (단, 점이 연속되거나 시작/끝에 있지 않아야 함)
    # RFC 1035를 준수하는 간소화된 검사
    subdomain_pattern = r'^(?!-)[a-zA-Z0-9-]+(\.[a-zA-Z0-9-]+)*$(?<!-)'
    
    # 서브도메인 접두사의 각 부분 검증
    subdomain_parts = subdomain_prefix.split('.')
    for part in subdomain_parts:
        if not part:  # 빈 부분 (연속된 점)
            return f"https://{domain}"
        if len(part) > 63:  # RFC 1035 최대 길이
            return f"https://{domain}"
        if not re.match(r'^[a-zA-Z0-9-]+$', part):
            return f"https://{domain}"
        if part.startswith('-') or part.endswith('-'):
            return f"https://{domain}"
    
    # 전체 서브도메인 접두사 패턴 검증
    if not re.match(subdomain_pattern, subdomain_prefix):
        return f"https://{domain}"
    
    # 유효한 서브도메인 접두사인 경우 URL 생성
    return f"https://{subdomain_prefix}.{domain}"