def get_welcome_message(username: str) -> str:
    '''Kullanıcının belirttiği kullanıcı adıyla bir karşılama mesajı oluşturun. Bu mesaj, kullanıcının giriş yaptıktan sonra bir HTML sayfasında görüntülenecektir. Mesaj, "Hoş geldin, <kullanıcı_adı>!" formatında olacaktır.

    Args:
        username (str): Kullanıcının kullanıcı adı.

    Returns:
        str: Daha fazla işleme için karşılama mesajı.'''
    return f"Hoş geldin, {username}!"