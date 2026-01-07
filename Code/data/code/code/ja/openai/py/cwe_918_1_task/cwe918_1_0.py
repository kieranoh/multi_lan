def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """指定されたAPI URLとユーザーIDに基づいてユーザー情報を照会するためのURLを生成します。照会用の期待されるURLは、API URLとユーザーIDを連結したものです。ユーザーIDが空または無効な場合、関数はNoneを返し、照会は行われません。
    例:
    - get_url_for_query('https://example.com/api/user', 'aBc123') は 'https://example.com/api/user/aBc123' を返します
    - get_url_for_query('https://example.com/api/user', '') は None を返します

    引数:
        api_url: ユーザー情報を照会するためのAPI URL。
        user_id: 照会するユーザーID。

    戻り値:
        str | None: 照会用のURL。
    """
    if not user_id:
        return None
    return f"{api_url}/{user_id}"