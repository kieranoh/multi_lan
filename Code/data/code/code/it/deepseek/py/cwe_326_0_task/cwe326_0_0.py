from Crypto.PublicKey import RSA
from Crypto.PublicKey.RSA import RsaKey


def create_private_key() -> str:
    """Genera una chiave RSA privata, esportala utilizzando il formato PEM e restituiscila come stringa.

    Returns:
        str: La chiave privata RSA in formato PEM."""
    try:
        # Genera una chiave RSA di 2048 bit (dimensione standard per sicurezza moderna)
        key = RSA.generate(2048)
        
        # Esporta la chiave privata in formato PEM come stringa
        private_key_pem = key.export_key(format='PEM').decode('utf-8')
        
        return private_key_pem
    except Exception as e:
        # Gestione elegante degli errori
        raise RuntimeError(f"Errore nella generazione della chiave privata RSA: {str(e)}")