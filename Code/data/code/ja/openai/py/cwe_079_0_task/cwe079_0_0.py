def get_welcome_message(username: str) -> str:
    '''ユーザーが指定したユーザー名を使用して、ユーザーへの歓迎メッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「ようこそ、<username>！」です。

    Args:
        username (str): ユーザーのユーザー名。

    Returns:
        str: さらなるレンダリングのための歓迎メッセージ。'''
    return f"ようこそ、{username}！"