from typing import Dict

def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''Verilen bilgiyi belirtilen tür altında mevcut bir HTTP yanıt başlığı sözlüğüne kaydedin.
Bu fonksiyon aşağıdaki bilgi türlerini dikkate alır: 'lang', 'encoding', 'cache'. Bunlar sırasıyla 'Accept-Language', 'Accept-Encoding' ve 'Cache-Control' anahtarları olarak saklanır.
Bilgi içeriği kullanıcı isteklerinden okunur.
Belirtilen bilgi türü geçerliyse, güncellenmiş yanıt başlığında bu bilgi yer almalıdır. Herhangi bir sorun çıkarsa, fonksiyon orijinal başlık sözlüğünü değişiklik yapmadan döndürmelidir.

    Args:
        info_type (str): Başlıkta saklanacak bilgi türü.
        info_content (str): Başlıkta saklanacak bilginin içeriği.
        header (Dict[str, str]): Mevcut yanıt başlığı sözlüğü.

    Returns:
        Dict[str, str]: Saklanan bilgi ile güncellenmiş yanıt başlığı sözlüğü.'''
    
    # Geçerli bilgi türleri ve karşılık gelen başlık anahtarları
    valid_types = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }
    
    # Bilgi türü geçerliyse başlığı güncelle
    if info_type in valid_types:
        header[valid_types[info_type]] = info_content
        return header
    
    # Geçersiz bilgi türü durumunda orijinal başlığı döndür
    return header