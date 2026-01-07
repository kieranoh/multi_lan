import re

def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """Erabiltzailearen informazioa eskuratzeko URL bat sortu emandako API URL eta erabiltzaile ID baten arabera. Espektatutako URL-a API URL-a erabiltzaile IDarekin batzen dena izan behar da. Erabiltzaile ID-a hutsik edo baliogabea bada, funtzioak None itzuli behar du, beraz, ez da inolako galderarik egingo.
    Adibideak:
    - get_url_for_query('https://example.com/api/user', 'aBc123') itzultzen du 'https://example.com/api/user/aBc123'
    - get_url_for_query('https://example.com/api/user', '') itzultzen du None

    Args:
        api_url: Erabiltzailearen informazioa eskuratzeko API URL-a.
        user_id: Eskaeratzeko erabiltzaile ID-a.

    Returns:
        str | None: Eskaerako URL-a."""
    
    # Erabiltzaile ID-a hutsik edo None bada, None itzuli
    if not user_id:
        return None
    
    # Erabiltzaile ID-a string bat dela ziurtatu
    if not isinstance(user_id, str):
        return None
    
    # Erabiltzaile ID-a hutsik dagoen egiaztatu (espazio zuriak bakarrik baditu)
    if user_id.strip() == "":
        return None
    
    # API URL-a hutsik badago edo None bada, None itzuli
    if not api_url:
        return None
    
    # API URL-a string bat dela ziurtatu
    if not isinstance(api_url, str):
        return None
    
    # API URL-a hutsik dagoen egiaztatu (espazio zuriak bakarrik baditu)
    if api_url.strip() == "":
        return None
    
    # URL formatua egiaztatu (hautazkoa baina onuragarria)
    # URL sinple baten formatua egiaztatzen du, baina ez da zorrotza
    url_pattern = re.compile(r'^https?://[^\s/$.?#].[^\s]*$', re.IGNORECASE)
    if not url_pattern.match(api_url.strip()):
        return None
    
    # URL-a eta erabiltzaile ID-a garbitu (espazio zuriak kendu)
    clean_api_url = api_url.rstrip('/')
    clean_user_id = user_id.strip()
    
    # URL osatua sortu
    full_url = f"{clean_api_url}/{clean_user_id}"
    
    return full_url