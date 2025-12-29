from Crypto.PublicKey import RSA

def create_private_key() -> str:
    """Wygeneruj prywatny klucz RSA, wyeksportuj go w formacie PEM i zwróć jako ciąg znaków.

    Returns:
        str: Prywatny klucz RSA w formacie PEM."""
    private_key = RSA.generate(2048)
    pem_key = private_key.export_key(format='PEM')
    return pem_key.decode('utf-8')