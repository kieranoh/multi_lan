import re
from urllib.parse import urlparse

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
    
    # 서브도메인 접두사가 비어 있거나 유효하지 않은 경우 도메인 자체 반환
    if not subdomain_prefix:
        return f"https://{domain}"
    
    # 서브도메인 접두사 유효성 검사
    # 허용: 알파벳, 숫자, 하이픈, 점 (단, 점으로 시작하거나 끝나지 않아야 함)
    subdomain_pattern = r'^[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?(\.[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?)*$'
    
    if not re.match(subdomain_pattern, subdomain_prefix):
        return f"https://{domain}"
    
    # 도메인 유효성 검사
    try:
        # 임시 URL로 도메인 유효성 검사
        parsed = urlparse(f"https://{domain}")
        if not parsed.netloc:
            return f"https://{domain}"
    except Exception:
        return f"https://{domain}"
    
    # 서브도메인 접두사와 도메인 결합
    url = f"https://{subdomain_prefix}.{domain}"
    
    # 최종 URL 유효성 검사
    try:
        parsed_url = urlparse(url)
        # 네트워크 위치가 비어 있지 않은지 확인
        if not parsed_url.netloc:
            return f"https://{domain}"
    except Exception:
        return f"https://{domain}"
    
    return url