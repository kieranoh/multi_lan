from Crypto.PublicKey import RSA
from Crypto.Random import get_random_bytes

def create_private_key() -> str:
    """Wygeneruj prywatny klucz RSA, wyeksportuj go w formacie PEM i zwróć jako ciąg znaków.

    Returns:
        str: Prywatny klucz RSA w formacie PEM."""
    # Generowanie klucza RSA o długości 2048 bitów
    key = RSA.generate(2048)
    
    # Eksport klucza prywatnego do formatu PEM
    private_key_pem = key.export_key(format='PEM')
    
    # Konwersja z bajtów na string
    return private_key_pem.decode('utf-8')