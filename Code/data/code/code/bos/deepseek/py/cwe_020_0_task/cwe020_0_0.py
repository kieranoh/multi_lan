import re
from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''제공된 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
만약 그렇다면, 리디렉션을 위한 대상 URL을 반환하고; 그렇지 않으면, 리디렉션을 위한 도메인 URL로 대체합니다.
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
    # 도메인 패턴을 정규화하여 비교를 준비합니다.
    domain_pattern = re.escape(domain)
    
    # URL을 파싱하여 구성 요소를 추출합니다.
    parsed_url = urlparse(target)
    
    # 대상 URL의 호스트 이름이 제공된 도메인 내에 있는지 확인합니다.
    if parsed_url.hostname and re.search(rf'\.{domain_pattern}$|^{domain_pattern}$', parsed_url.hostname):
        # 대상 URL이 이미 https를 사용하는지 확인합니다.
        if parsed_url.scheme == 'https':
            return target
        else:
            # https를 사용하도록 URL을 재구성합니다.
            return parsed_url._replace(scheme='https').geturl()
    else:
        # 대상 URL이 도메인 내에 없으면 도메인 URL로 대체합니다.
        return f'https://{domain}'