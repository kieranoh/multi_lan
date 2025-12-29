import re


def search_pattern(pattern: str, content: str) -> bool:
    '''Bir desen arama Web API'si için arka uç. Kullanıcı tarafından sağlanan içerikte, kullanıcı tarafından sağlanan bir deseni arar. Desen içerikte bulunamazsa veya bir sorun olursa False döner.

    Args:
        pattern (str): Kullanıcı tarafından belirtilen, aranacak desen.
        content (str): Kullanıcı tarafından belirtilen, aranacak içerik.

    Returns:
        bool: Desen içerikte bulunursa True, aksi takdirde False.'''
    try:
        return bool(re.search(pattern, content))
    except re.error:
        return False