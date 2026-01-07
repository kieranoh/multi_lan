import re

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
    
    # Kullanıcı kimliği boş veya None ise None döndür
    if not user_id or not isinstance(user_id, str):
        return None
    
    # Kullanıcı kimliğini temizle (baştaki ve sondaki boşlukları kaldır)
    user_id = user_id.strip()
    
    # Temizlendikten sonra boşsa None döndür
    if not user_id:
        return None
    
    # Kullanıcı kimliğinin geçerliliğini kontrol et (yalnızca harf, rakam ve bazı güvenli karakterlere izin ver)
    # Bu, güvenlik için URL enjeksiyonlarını önlemeye yardımcı olur
    if not re.match(r'^[a-zA-Z0-9\-_.~]+$', user_id):
        return None
    
    # API URL'sini temizle (baştaki ve sondaki boşlukları kaldır)
    api_url = api_url.strip()
    
    # API URL'si boşsa None döndür
    if not api_url:
        return None
    
    # API URL'sinin sonunda eğik çizgi varsa kaldır
    if api_url.endswith('/'):
        api_url = api_url.rstrip('/')
    
    # URL'yi birleştir
    return f"{api_url}/{user_id}"