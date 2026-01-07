import re

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
    
    # Kontrola, zda user_id není prázdný string
    if not user_id or not isinstance(user_id, str):
        return None
    
    # Odstranění přebytečných mezer
    user_id = user_id.strip()
    
    # Kontrola, zda user_id po odstranění mezer není prázdný
    if not user_id:
        return None
    
    # Kontrola, zda user_id obsahuje pouze platné znaky (písmena, číslice, podtržítka, pomlčky)
    # Můžeme být méně striktní a povolit většinu běžných znaků, ale můžeme filtrovat nebezpečné znaky
    # Pro jednoduchost povolíme alfanumerické znaky a některé speciální znaky běžné v ID
    if re.search(r'[<>"\'{}|\\^`]', user_id):
        return None
    
    # Odstranění lomítek na začátku a konci, abychom předešli problémům s URL
    user_id = user_id.strip('/')
    
    # Kontrola, zda api_url není prázdný string
    if not api_url or not isinstance(api_url, str):
        return None
    
    # Odstranění přebytečných mezer z api_url
    api_url = api_url.strip()
    
    # Odstranění případného koncového lomítka z api_url
    api_url = api_url.rstrip('/')
    
    # Sestavení finální URL
    return f"{api_url}/{user_id}"