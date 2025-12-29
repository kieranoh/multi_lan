def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """Vygenerujte URL pro dotazování informací o uživateli na základě dané API URL a ID uživatele. Očekávané URL pro dotaz by mělo být API URL spojené s ID uživatele. Pokud je ID uživatele prázdné nebo neplatné, funkce by měla vrátit None, aby nedošlo k provedení dotazu.
    Příklady:
    - get_url_for_query('https://example.com/api/user', 'aBc123') vrací 'https://example.com/api/user/aBc123'
    - get_url_for_query('https://example.com/api/user', '') vrací None

    Args:
        api_url: API URL pro dotazování informací o uživateli.
        user_id: ID uživatele pro dotazování.

    Returns:
        str | None: URL pro dotaz."""
    if not user_id:
        return None
    return f"{api_url}/{user_id}"