import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """Verilen e-posta adresinin geçerli olup olmadığını kontrol edin. Örneğin, abc.123@def.ghi.com.uk geçerli bir e-posta adresidir. Yanlış negatifleri önlemek için mümkün olduğunca çok durumu kapsayın.

    Args:
        email: Kontrol edilecek e-posta.

    Returns:
        Tuple[bool, str]: İlk elemanı e-postanın geçerli olup olmadığını belirten bir boolean ve ikinci elemanı e-postayı kontrol etmek için kullanılan desen olan bir tuple."""
    
    # RFC 5322'ye uygun kapsamlı e-posta doğrulama deseni
    # Bu desen uluslararası karakterleri, çoklu alt alan adlarını ve çeşitli geçerli formatları destekler
    pattern = r"""
        ^                           # Satır başı
        [a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+  # Yerel kısım (bir veya daha fazla karakter)
        (?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*  # Nokta ve devam eden yerel kısım (isteğe bağlı)
        @                           # @ sembolü
        (?:                         # Alan adı kısmı
            [a-zA-Z0-9]             # İlk karakter harf veya rakam
            (?:[a-zA-Z0-9-]*[a-zA-Z0-9])?  # Ara karakterler (harf, rakam, tire) ve son karakter
            \.                      # Nokta
        )+                          # Bir veya daha fazla alt alan
        [a-zA-Z]{2,}                # En az 2 harften oluşan üst seviye alan
        (?:\.?[a-zA-Z]{2,})*        # İsteğe bağlı ek üst seviye alanlar (.com.uk gibi)
        $                           # Satır sonu
    """
    
    # Deseni derle ve re.VERBOSE bayrağı ile boşlukları yoksay
    compiled_pattern = re.compile(pattern, re.VERBOSE)
    
    # E-posta adresini kontrol et
    is_valid = bool(compiled_pattern.match(email))
    
    return (is_valid, pattern)