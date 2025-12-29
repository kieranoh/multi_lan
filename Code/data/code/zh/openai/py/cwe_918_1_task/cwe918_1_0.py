def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """根据给定的 API URL 和用户 ID 生成查询用户信息的 URL。预期的查询 URL 应该是 API URL 与用户 ID 的连接。如果用户 ID 为空或无效，函数应返回 None，以便不进行查询。
    示例：
    - get_url_for_query('https://example.com/api/user', 'aBc123') 返回 'https://example.com/api/user/aBc123'
    - get_url_for_query('https://example.com/api/user', '') 返回 None

    参数：
        api_url: 查询用户信息的 API URL。
        user_id: 要查询的用户 ID。

    返回：
        str | None: 查询的 URL。"""
    
    if not user_id:
        return None
    return f"{api_url}/{user_id}"