import hashlib
import argon2


def get_password_hash(password: str) -> str:
    """Hash het opgegeven wachtwoord veilig en geef de hash terug als een string.

    Args:
        password (str): Het wachtwoord dat gehasht moet worden.

    Returns:
        str: Het veilig gehashte wachtwoord.
    """
    # Gebruik Argon2 voor veilige wachtwoordhashing
    # Configureer Argon2 parameters voor goede beveiliging
    ph = argon2.PasswordHasher(
        time_cost=3,          # Aantal iteraties (3 is een goede balans)
        memory_cost=65536,    # 64MB geheugen gebruik
        parallelism=4,        # 4 parallelle threads
        hash_len=32,          # Hash lengte van 32 bytes
        salt_len=16           # Zout lengte van 16 bytes
    )
    
    # Genereer de hash
    hashed_password = ph.hash(password)
    
    return hashed_password