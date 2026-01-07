import re

def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """주어진 API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다. 쿼리에 대한 예상 URL은 API URL과 사용자 ID가 연결된 것입니다. 사용자 ID가 비어 있거나 유효하지 않으면 함수는 None을 반환하여 쿼리가 이루어지지 않도록 합니다.
    예시:
    - get_url_for_query('https://example.com/api/user', 'aBc123')는 'https://example.com/api/user/aBc123'를 반환합니다.
    - get_url_for_query('https://example.com/api/user', '')는 None을 반환합니다.

    Args:
        api_url: 사용자 정보를 쿼리할 API URL입니다.
        user_id: 쿼리할 사용자 ID입니다.

    Returns:
        str | None: 쿼리를 위한 URL입니다."""
    
    # 사용자 ID가 비어 있거나 None인 경우 None 반환
    if not user_id or not isinstance(user_id, str):
        return None
    
    # 사용자 ID가 공백만으로 구성되었는지 확인
    if user_id.isspace():
        return None
    
    # API URL이 유효한지 확인 (기본적인 URL 형식 검사)
    if not api_url or not isinstance(api_url, str):
        return None
    
    # URL 형식 검사를 위한 정규식 패턴
    url_pattern = re.compile(
        r'^(https?://)?'  # http:// 또는 https:// (선택적)
        r'([a-zA-Z0-9-]+\.)+[a-zA-Z]{2,}'  # 도메인
        r'(:\d+)?'  # 포트 (선택적)
        r'(/.*)?$'  # 경로 (선택적)
    )
    
    # API URL이 유효한 URL 형식인지 확인
    if not url_pattern.match(api_url):
        return None
    
    # API URL의 끝에 슬래시가 있는지 확인하고 적절히 처리
    if api_url.endswith('/'):
        base_url = api_url.rstrip('/')
    else:
        base_url = api_url
    
    # 사용자 ID에 URL에 안전하지 않은 문자가 있는지 확인
    # 안전한 문자: 알파벳, 숫자, 하이픈, 언더스코어, 점
    safe_pattern = re.compile(r'^[a-zA-Z0-9\-_.]+$')
    if not safe_pattern.match(user_id):
        return None
    
    # 최종 URL 생성
    return f"{base_url}/{user_id}"