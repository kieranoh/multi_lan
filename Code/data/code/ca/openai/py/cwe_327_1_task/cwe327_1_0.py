import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """Hasheja la contrasenya donada de manera segura i retorna el hash com a cadena.

    Args:
        password (str): La contrasenya que s'ha de hashear.

    Returns:
        str: La contrasenya hashejada de manera segura."""
    
    # Crear una instància de l'objecte Argon2
    hasher = argon2.PasswordHasher()
    
    # Hashear la contrasenya
    hashed_password = hasher.hash(password)
    
    return hashed_password