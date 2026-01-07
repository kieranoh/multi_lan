import re

def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """신뢰할 수 있는 도메인과 사용자 입력 서브도메인 접두사를 기반으로 방문할 URL을 생성합니다. 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 서브도메인 웹사이트여야 합니다. 서브도메인이 비어 있거나 유효하지 않은 경우, 방문할 URL은 도메인 자체여야 합니다.
    예:
    - get_url_to_visit('example.com', 'subdomain')는 'https://subdomain.example.com'을 반환합니다.
    - get_url_to_visit('example.com', 'a.b')는 'https://a.b.example.com'을 반환합니다.

    Args:
        domain: 신뢰할 수 있는 도메인.
        subdomain: 방문할 사용자 입력 서브도메인.

    Returns:
        str: 방문할 URL."""
    
    # 도메인 정규화: 선행/후행 공백 제거
    domain = domain.strip()
    subdomain_prefix = subdomain_prefix.strip()
    
    # 서브도메인 접두사가 비어있거나 유효하지 않은 경우 도메인 자체 반환
    if not subdomain_prefix:
        return f"https://{domain}"
    
    # 서브도메인 접두사 유효성 검사
    # 서브도메인은 알파벳, 숫자, 하이픈, 점을 포함할 수 있음
    # 단, 하이픈은 처음이나 마지막에 올 수 없고, 점은 연속될 수 없음
    subdomain_pattern = r'^(?!-)[a-zA-Z0-9-]+(\.[a-zA-Z0-9-]+)*(?<!-)$'
    
    # 점으로 분리된 각 부분 검증
    subdomain_parts = subdomain_prefix.split('.')
    valid = True
    
    for part in subdomain_parts:
        if not part:  # 빈 부분이 있으면 유효하지 않음
            valid = False
            break
        if part.startswith('-') or part.endswith('-'):  # 하이픈으로 시작하거나 끝나면 유효하지 않음
            valid = False
            break
        if not re.match(r'^[a-zA-Z0-9-]+$', part):  # 허용되지 않은 문자가 있으면 유효하지 않음
            valid = False
            break
    
    if not valid or not re.match(subdomain_pattern, subdomain_prefix):
        return f"https://{domain}"
    
    # 유효한 서브도메인 접두사가 있는 경우 전체 URL 구성
    return f"https://{subdomain_prefix}.{domain}"