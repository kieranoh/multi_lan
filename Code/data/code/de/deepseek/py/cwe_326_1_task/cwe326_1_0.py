from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes

def create_private_key_dsa() -> str:
    """Generiere einen privaten DSA-Schlüssel, exportiere ihn im PEM-Format und gib ihn als String zurück.

    Returns:
        str: Der DSA-private Schlüssel im PEM-Format."""
    # Generiere einen neuen DSA-Schlüssel mit einer Schlüssellänge von 2048 Bits
    key = DSA.generate(2048)
    
    # Exportiere den privaten Schlüssel im PEM-Format
    private_key_pem = key.export_key(format='PEM')
    
    # Konvertiere von Bytes zu String, falls nötig
    if isinstance(private_key_pem, bytes):
        private_key_pem = private_key_pem.decode('utf-8')
    
    return private_key_pem