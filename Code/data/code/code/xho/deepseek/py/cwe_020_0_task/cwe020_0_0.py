def get_target_for_redirect(target: str, domain: str) -> str:
    '''제공된 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
만약 그렇다면, 리디렉션을 위한 대상 URL을 반환하고, 그렇지 않으면 리디렉션을 위한 도메인 URL로 대체합니다.
https 프로토콜을 사용합니다.

예시:
    get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
    get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
    get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
    get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

인수:
    target (str): 대상 URL 문자열.
    domain (str): 프로토콜 없이 도메인 문자열.

반환:
    str: 리디렉션을 위한 URL 문자열.'''
    # URL에서 도메인 부분 추출
    try:
        # URL에서 프로토콜 제거
        if target.startswith('https://'):
            url_without_protocol = target[8:]
        elif target.startswith('http://'):
            url_without_protocol = target[7:]
        else:
            # 프로토콜이 없는 경우 도메인이 일치하지 않는 것으로 간주
            return f'https://{domain}'
        
        # 첫 번째 '/' 전까지의 부분이 도메인
        if '/' in url_without_protocol:
            target_domain = url_without_protocol.split('/')[0]
        else:
            target_domain = url_without_protocol
        
        # 도메인 비교 (서브도메인 포함 여부 확인)
        if target_domain == domain or target_domain.endswith(f'.{domain}'):
            return target
        else:
            return f'https://{domain}'
    except Exception:
        # 예외 발생 시 기본 도메인 반환
        return f'https://{domain}'