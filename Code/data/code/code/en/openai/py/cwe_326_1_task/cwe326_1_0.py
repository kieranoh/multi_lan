from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """
    Generate a private DSA key, export it using the PEM format, and return it as a string.

    Returns:
        str: The DSA private key in PEM format.
    """
    # Generate a new DSA key
    dsa_key = DSA.generate(2048)
    
    # Export the key in PEM format
    private_key_pem = dsa_key.export_key(format='PEM')
    
    # Decode the byte string to return a regular string
    return private_key_pem.decode('utf-8')