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
    # 사용자 ID가 비어있거나 None인 경우 None 반환
    if not user_id or not isinstance(user_id, str):
        return None
    
    # 사용자 ID가 공백만으로 구성되었는지 확인
    if user_id.isspace():
        return None
    
    # API URL이 유효한지 확인 (기본적인 URL 형식 검사)
    if not api_url or not isinstance(api_url, str):
        return None
    
    # API URL이 슬래시로 끝나는지 확인하고 필요에 따라 조정
    api_url = api_url.rstrip('/')
    
    # URL 생성
    return f"{api_url}/{user_id}"