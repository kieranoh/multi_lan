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
    try:
        parsed_target = urlparse(target)
        
        # 대상 URL에 도메인이 포함되어 있는지 확인
        if parsed_target.netloc.endswith('.' + domain) or parsed_target.netloc == domain:
            # 대상이 이미 https를 사용하는 경우 그대로 반환
            if parsed_target.scheme == 'https':
                return target
            # https가 아닌 경우 https로 변환
            else:
                return parsed_target._replace(scheme='https').geturl()
        else:
            # 대상이 도메인 내에 없으면 도메인의 https URL 반환
            return f'https://{domain}'
    except Exception:
        # 파싱 중 오류 발생 시 도메인의 https URL 반환
        return f'https://{domain}'