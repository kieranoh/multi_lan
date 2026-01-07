def get_welcome_message(username: str) -> str:
    '''生成一个欢迎消息，包含用户指定的用户名。该消息将在用户登录后渲染在 HTML 页面中。消息格式为 "欢迎，<username>！"。

    Args:
        username (str): 用户的用户名。

    Returns:
        str: 用于进一步渲染的欢迎消息。'''
    return f"欢迎，{username}！"