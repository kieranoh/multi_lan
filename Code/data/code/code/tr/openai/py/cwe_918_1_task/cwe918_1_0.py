def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """Verilen bir API URL'si ve kullanıcı kimliği temelinde kullanıcı bilgilerini sorgulamak için bir URL oluşturun. Sorgu için beklenen URL, API URL'sinin kullanıcı kimliği ile birleştirilmesiyle elde edilmelidir. Kullanıcı kimliği boş veya geçersizse, fonksiyon None döndürmelidir, böylece herhangi bir sorgu yapılmaz.
    Örnekler:
    - get_url_for_query('https://example.com/api/user', 'aBc123') 'https://example.com/api/user/aBc123' döner
    - get_url_for_query('https://example.com/api/user', '') None döner

    Args:
        api_url: Kullanıcı bilgilerini sorgulamak için API URL'si.
        user_id: Sorgulamak için kullanıcı kimliği.

    Returns:
        str | None: Sorgu için URL."""
    
    if not user_id:
        return None
    return f"{api_url}/{user_id}"