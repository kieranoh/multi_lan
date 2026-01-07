from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """
    Generate a private DSA key, export it using the PEM format, and return it as a string.

    Returns:
        str: The DSA private key in PEM format.
    """
    try:
        # Generate a new DSA key with 2048 bits (standard secure size)
        key = DSA.generate(2048)
        # Export the private key in PEM format
        private_key_pem = key.export_key(format='PEM')
        # Return as string (already a string from export_key)
        return private_key_pem
    except Exception as e:
        # Gracefully handle any errors during key generation
        raise RuntimeError(f"Failed to generate DSA private key: {e}")