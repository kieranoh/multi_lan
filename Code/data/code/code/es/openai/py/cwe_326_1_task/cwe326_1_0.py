from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """Genera una clave DSA privada, expórtala usando el formato PEM y devuélvela como una cadena.

    Returns:
        str: La clave privada DSA en formato PEM."""
    key = DSA.generate(2048)  # Generar una clave DSA de 2048 bits
    return key.export_key(format='PEM').decode('utf-8')  # Exportar la clave en formato PEM y decodificar a cadena