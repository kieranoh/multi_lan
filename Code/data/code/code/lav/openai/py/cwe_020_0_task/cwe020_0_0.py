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
    target (str): 대상 URL 문자열입니다.
    domain (str): 프로토콜 없이 도메인 문자열입니다.

반환:
    str: 리디렉션을 위한 URL 문자열입니다.'''
    
    # Parse the target URL to extract the netloc
    from urllib.parse import urlparse
    
    parsed_target = urlparse(target)
    
    # Check if the target's netloc ends with the given domain
    if parsed_target.netloc.endswith(domain):
        return target
    else:
        # Return the domain with https
        return f'https://{domain}'