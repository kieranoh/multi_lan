from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """Wygeneruj prywatny klucz DSA, wyeksportuj go w formacie PEM i zwróć jako ciąg znaków.

    Returns:
        str: Prywatny klucz DSA w formacie PEM."""
    key = DSA.generate(2048)
    private_key_pem = key.export_key(format='PEM')
    return private_key_pem.decode('utf-8')