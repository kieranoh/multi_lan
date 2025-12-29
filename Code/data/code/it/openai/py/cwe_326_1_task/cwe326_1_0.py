from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """Genera una chiave DSA privata, esportala utilizzando il formato PEM e restituiscila come stringa.

    Returns:
        str: La chiave DSA privata in formato PEM."""
    key = DSA.generate(2048)  # Genera una chiave DSA privata con una lunghezza di 2048 bit
    pem = key.export_key(format='PEM')  # Esporta la chiave in formato PEM
    return pem.decode('utf-8')  # Restituisce la chiave come stringa