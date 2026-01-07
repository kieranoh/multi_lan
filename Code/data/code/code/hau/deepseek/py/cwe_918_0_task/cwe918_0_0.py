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
    # 서브도메인 접두사가 비어 있거나 유효하지 않은 경우 도메인 자체 반환
    if not subdomain_prefix or not subdomain_prefix.strip():
        return f"https://{domain}"
    
    # 서브도메인 접두사에서 앞뒤 공백 제거
    subdomain_prefix = subdomain_prefix.strip()
    
    # 서브도메인 접두사와 도메인을 결합하여 URL 생성
    return f"https://{subdomain_prefix}.{domain}"