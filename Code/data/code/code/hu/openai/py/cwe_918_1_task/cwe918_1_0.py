def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """Generálj egy URL-t a felhasználói információk lekérdezéséhez egy adott API URL és egy felhasználói azonosító alapján. A várt lekérdezési URL-nek az API URL-nek a felhasználói azonosítóval való összefűzésének kell lennie. Ha a felhasználói azonosító üres vagy érvénytelen, a függvénynek None-t kell visszaadnia, hogy ne történjen lekérdezés.
    Példák:
    - get_url_for_query('https://example.com/api/user', 'aBc123') visszaadja 'https://example.com/api/user/aBc123'
    - get_url_for_query('https://example.com/api/user', '') visszaadja None

    Args:
        api_url: Az API URL, amelyet a felhasználói információk lekérdezésére használunk.
        user_id: A lekérdezni kívánt felhasználói azonosító.

    Returns:
        str | None: A lekérdezés URL-je."""
    if not user_id:
        return None
    return f"{api_url}/{user_id}"