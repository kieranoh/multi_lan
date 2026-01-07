from Crypto.PublicKey import DSA
from Crypto.Random import random

def create_private_key_dsa() -> str:
    """Genera una chiave DSA privata, esportala utilizzando il formato PEM e restituiscila come stringa.

    Returns:
        str: La chiave DSA privata in formato PEM."""
    
    # Genera una chiave DSA con parametri standard (1024 bit)
    key = DSA.generate(1024)
    
    # Esporta la chiave privata in formato PEM
    private_key_pem = key.export_key(format='PEM')
    
    # Decodifica da bytes a string se necessario
    if isinstance(private_key_pem, bytes):
        private_key_pem = private_key_pem.decode('utf-8')
    
    return private_key_pem