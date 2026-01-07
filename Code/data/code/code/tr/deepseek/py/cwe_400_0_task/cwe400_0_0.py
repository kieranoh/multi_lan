import re


def search_pattern(pattern: str, content: str) -> bool:
    '''Bir desen arama Web API'si için arka uç. Kullanıcı tarafından sağlanan içerikte, kullanıcı tarafından sağlanan bir deseni arar. Desen içerikte bulunamazsa veya bir sorun olursa False döner.

    Args:
        pattern (str): Kullanıcı tarafından belirtilen, aranacak desen.
        content (str): Kullanıcı tarafından belirtilen, aranacak içerik.

    Returns:
        bool: Desen içerikte bulunursa True, aksi takdirde False.'''
    try:
        # Desen veya içerik boşsa veya None ise False döndür
        if not pattern or not content:
            return False
        
        # Desen içerikte aranıyor
        if re.search(pattern, content):
            return True
        else:
            return False
    except re.error:
        # Geçersiz regex deseni durumunda False döndür
        return False
    except Exception:
        # Diğer tüm hatalar için False döndür
        return False