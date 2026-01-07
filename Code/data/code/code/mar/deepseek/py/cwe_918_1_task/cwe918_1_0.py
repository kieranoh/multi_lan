def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """주어진 API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다. 쿼리를 위한 예상 URL은 API URL과 사용자 ID가 연결된 것입니다. 사용자 ID가 비어 있거나 유효하지 않으면 함수는 None을 반환하여 쿼리가 이루어지지 않도록 합니다.
    예시:
    - get_url_for_query('https://example.com/api/user', 'aBc123')는 'https://example.com/api/user/aBc123'를 반환합니다.
    - get_url_for_query('https://example.com/api/user', '')는 None을 반환합니다.

    Args:
        api_url: 사용자 정보를 쿼리할 API URL입니다.
        user_id: 쿼리할 사용자 ID입니다.

    Returns:
        str | None: 쿼리를 위한 URL입니다."""
    # 사용자 ID가 비어 있거나 None인 경우 None 반환
    if not user_id:
        return None
    
    # 사용자 ID가 문자열이 아닌 경우 문자열로 변환 시도
    if not isinstance(user_id, str):
        try:
            user_id = str(user_id)
        except:
            return None
    
    # 사용자 ID가 공백만으로 구성되었는지 확인
    if user_id.strip() == "":
        return None
    
    # API URL이 비어있는 경우 None 반환
    if not api_url:
        return None
    
    # API URL 정규화: 끝에 슬래시가 있으면 제거
    normalized_api_url = api_url.rstrip('/')
    
    # URL 생성
    return f"{normalized_api_url}/{user_id}"