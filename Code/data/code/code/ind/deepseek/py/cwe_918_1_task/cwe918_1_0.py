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
        str | None: 쿼리용 URL입니다."""
    # 사용자 ID가 비어있는지 확인
    if not user_id or not user_id.strip():
        return None
    
    # 사용자 ID가 유효한지 확인 (알파벳, 숫자, 하이픈, 언더스코어만 허용)
    # 실제 요구사항에 따라 이 검증 로직은 조정될 수 있습니다
    if not re.match(r'^[a-zA-Z0-9_-]+$', user_id):
        return None
    
    # API URL이 슬래시로 끝나지 않으면 추가
    if not api_url.endswith('/'):
        api_url += '/'
    
    # URL 생성
    return f"{api_url}{user_id}"