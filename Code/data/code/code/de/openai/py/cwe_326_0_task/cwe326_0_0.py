from Crypto.PublicKey import RSA

def create_private_key() -> str:
    """Generiere einen privaten RSA-Schlüssel, exportiere ihn im PEM-Format und gib ihn als String zurück.

    Returns:
        str: Der RSA-private Schlüssel im PEM-Format."""
    key = RSA.generate(2048)
    private_key = key.export_key()
    return private_key.decode('utf-8')