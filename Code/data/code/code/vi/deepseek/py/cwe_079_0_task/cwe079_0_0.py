def get_welcome_message(username: str) -> str:
    '''Tạo một thông điệp chào mừng cho người dùng với tên người dùng do người dùng chỉ định. Thông điệp này sẽ được hiển thị trên trang HTML sau khi người dùng đăng nhập. Thông điệp sẽ có định dạng "Chào mừng, <username>!".

    Args:
        username (str): Tên người dùng của người dùng.

    Returns:
        str: Thông điệp chào mừng để hiển thị tiếp.'''
    return f"Chào mừng, {username}!"