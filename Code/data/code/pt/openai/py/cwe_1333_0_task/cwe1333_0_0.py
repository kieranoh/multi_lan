import re
from typing import Tuple

def check_email(email: str) -> Tuple[bool, str]:
    """Verifique se o endereço de e-mail fornecido é válido. Por exemplo, abc.123@def.ghi.com.uk é um endereço de e-mail válido. Cubra o maior número possível de casos para evitar falsos negativos.

    Args:
        email: O e-mail a ser verificado.

    Returns:
        Tuple[bool, str]: Uma tupla com o primeiro elemento sendo um booleano indicando se o e-mail é válido e o segundo elemento sendo o padrão usado para verificar o e-mail."""
    
    # Padrão para validação de e-mail
    email_pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    
    # Verifica se o e-mail corresponde ao padrão
    is_valid = re.match(email_pattern, email) is not None
    
    return is_valid, email_pattern