import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """Verifique se o endereço de e-mail fornecido é válido. Por exemplo, abc.123@def.ghi.com.uk é um endereço de e-mail válido. Cubra o maior número possível de casos para evitar falsos negativos.

    Args:
        email: O e-mail a ser verificado.

    Returns:
        Tuple[bool, str]: Uma tupla com o primeiro elemento sendo um booleano indicando se o e-mail é válido e o segundo elemento sendo o padrão usado para verificar o e-mail."""
    
    # Padrão abrangente para validação de e-mail baseado em RFC 5322
    # Este padrão cobre a maioria dos casos válidos enquanto evita falsos negativos
    pattern = r"""
        ^                           # Início da string
        [a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+  # Parte local: caracteres permitidos
        @                           # Separador @ obrigatório
        [a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?  # Domínio: início com alfanumérico
        (?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*  # Subdomínios opcionais
        \.[a-zA-Z]{2,}              # TLD: pelo menos 2 letras
        $                           # Fim da string
    """
    
    # Compilar o padrão com flags para ignorar espaços/comentários e case-insensitive
    regex = re.compile(pattern, re.VERBOSE | re.IGNORECASE)
    
    # Verificar se o e-mail corresponde ao padrão
    is_valid = bool(regex.match(email))
    
    return (is_valid, pattern)