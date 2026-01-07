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
    
    # Geçerli bilgi türlerini ve karşılık gelen başlık anahtarlarını tanımla
    valid_info_types = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }
    
    # Bilgi türünün geçerli olup olmadığını kontrol et
    if info_type not in valid_info_types:
        return header
    
    # Başlık sözlüğünün bir kopyasını oluştur (orijinali değiştirmemek için)
    updated_header = header.copy()
    
    # İlgili başlık anahtarını al
    header_key = valid_info_types[info_type]
    
    # Bilgi içeriğini ilgili başlık anahtarına kaydet
    updated_header[header_key] = info_content
    
    return updated_header