from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """Generiere einen privaten DSA-Schlüssel, exportiere ihn im PEM-Format und gib ihn als String zurück.

    Returns:
        str: Der DSA-private Schlüssel im PEM-Format."""
    key = DSA.generate(2048)
    private_key_pem = key.export_key(format='PEM')
    return private_key_pem.decode('utf-8')