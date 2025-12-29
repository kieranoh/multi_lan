from Crypto.PublicKey import RSA

def create_private_key() -> str:
    """Genera una chiave RSA privata, esportala utilizzando il formato PEM e restituiscila come stringa.

    Returns:
        str: La chiave privata RSA in formato PEM."""
    # Genera una chiave RSA privata con una dimensione di 2048 bit
    private_key = RSA.generate(2048)
    # Esporta la chiave in formato PEM
    private_key_pem = private_key.export_key(format='PEM')
    # Restituisce la chiave privata come stringa
    return private_key_pem.decode('utf-8')