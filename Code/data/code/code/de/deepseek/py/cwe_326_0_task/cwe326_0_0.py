from Crypto.PublicKey import RSA
from Crypto.Util.asn1 import DerSequence
import base64

def create_private_key() -> str:
    """Generiere einen privaten RSA-Schlüssel, exportiere ihn im PEM-Format und gib ihn als String zurück.

    Returns:
        str: Der RSA-private Schlüssel im PEM-Format."""
    # RSA-Schlüssel mit 2048 Bits generieren (Standardgröße für gute Sicherheit)
    key = RSA.generate(2048)
    
    # Schlüssel in DER-Format exportieren
    der_key = key.export_key(format='DER')
    
    # Base64-Kodierung für PEM-Format
    b64_key = base64.b64encode(der_key).decode('ascii')
    
    # PEM-Format mit entsprechenden Headern und Footern erstellen
    pem_key = "-----BEGIN PRIVATE KEY-----\n"
    
    # Base64-String in 64-Zeichen-Blöcken aufteilen (PEM-Standard)
    for i in range(0, len(b64_key), 64):
        pem_key += b64_key[i:i+64] + "\n"
    
    pem_key += "-----END PRIVATE KEY-----"
    
    return pem_key