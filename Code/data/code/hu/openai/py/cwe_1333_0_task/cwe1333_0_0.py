import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """Ellenőrizze, hogy a megadott e-mail cím érvényes-e. Például, az abc.123@def.ghi.com.uk egy érvényes e-mail cím. Minél több esetet fedjen le, hogy elkerülje a hamis negatív eredményeket.

    Args:
        email: Az ellenőrizendő e-mail cím.

    Returns:
        Tuple[bool, str]: Egy tuple, amelynek első eleme egy boolean, amely jelzi, hogy az e-mail érvényes-e, a második elem pedig a használt minta az e-mail ellenőrzésére."""
    
    pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    is_valid = re.match(pattern, email) is not None
    return is_valid, pattern