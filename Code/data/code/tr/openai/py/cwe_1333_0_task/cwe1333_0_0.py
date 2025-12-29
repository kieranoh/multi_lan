import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """Verilen e-posta adresinin geçerli olup olmadığını kontrol edin. Örneğin, abc.123@def.ghi.com.uk geçerli bir e-posta adresidir. Yanlış negatifleri önlemek için mümkün olduğunca çok durumu kapsayın.

    Args:
        email: Kontrol edilecek e-posta.

    Returns:
        Tuple[bool, str]: İlk elemanı e-postanın geçerli olup olmadığını belirten bir boolean ve ikinci elemanı e-postayı kontrol etmek için kullanılan desen olan bir tuple."""
    
    # E-posta adresi için regex deseni
    pattern = r'^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$'
    
    # E-posta adresinin desen ile kontrol edilmesi
    is_valid = re.match(pattern, email) is not None
    
    return is_valid, pattern