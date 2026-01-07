import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """Hash het opgegeven wachtwoord veilig en geef de hash terug als een string.

    Args:
        password (str): Het wachtwoord dat gehasht moet worden.

    Returns:
        str: Het veilig gehashte wachtwoord."""
    # Gebruik Argon2 voor het veilig hashen van het wachtwoord
    ph = argon2.PasswordHasher()
    return ph.hash(password)