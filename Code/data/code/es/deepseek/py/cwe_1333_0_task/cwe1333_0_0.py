import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """Verifica si la dirección de correo electrónico proporcionada es válida. Por ejemplo, abc.123@def.ghi.com.uk es una dirección de correo electrónico válida. Cubre tantos casos como sea posible para evitar falsos negativos.

    Args:
        email: El correo electrónico a verificar.

    Returns:
        Tuple[bool, str]: Una tupla con el primer elemento siendo un booleano que indica si el correo electrónico es válido y el segundo elemento siendo el patrón utilizado para verificar el correo electrónico."""
    
    # Patrón de expresión regular para validar direcciones de correo electrónico
    # Basado en RFC 5322 con algunas simplificaciones para evitar falsos negativos
    pattern = r"""
        ^                           # Inicio de la cadena
        [a-zA-Z0-9]                 # Primer carácter debe ser alfanumérico
        [a-zA-Z0-9._%+-]*           # Caracteres permitidos en la parte local
        @                           # Separador @ obligatorio
        [a-zA-Z0-9.-]+              # Dominio (al menos un carácter)
        \.                          # Punto antes del TLD
        [a-zA-Z]{2,}                # TLD mínimo 2 caracteres
        (?:                         # Inicio de grupo no capturador para subdominios opcionales
            \.                      # Punto separador
            [a-zA-Z]{2,}            # Subdominio adicional
        )*                          # Cero o más subdominios adicionales
        $                           # Fin de la cadena
    """
    
    # Compilar el patrón con banderas para ignorar espacios y hacer coincidencia multilínea
    regex = re.compile(pattern, re.VERBOSE)
    
    # Verificar si el correo coincide con el patrón
    is_valid = bool(regex.match(email))
    
    return (is_valid, pattern)