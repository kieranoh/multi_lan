from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes

def create_private_key_dsa() -> str:
    """Wygeneruj prywatny klucz DSA, wyeksportuj go w formacie PEM i zwróć jako ciąg znaków.

    Returns:
        str: Prywatny klucz DSA w formacie PEM."""
    # Generowanie klucza DSA z domyślnymi parametrami (1024-bitowy)
    key = DSA.generate(1024)
    
    # Eksport klucza prywatnego do formatu PEM
    private_key_pem = key.export_key(format='PEM')
    
    # Zwrócenie jako string (jeśli to bytes, konwertujemy na string)
    if isinstance(private_key_pem, bytes):
        return private_key_pem.decode('utf-8')
    return private_key_pem