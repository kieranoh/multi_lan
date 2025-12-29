import hashlib
import argon2


def get_password_hash(password: str) -> str:
    """Hashen Sie das angegebene Passwort sicher und geben Sie den Hash als Zeichenfolge zurück.

    Args:
        password (str): Das zu hashende Passwort.

    Returns:
        str: Das sicher gehashte Passwort.
    """
    # Konfiguration für Argon2 mit sicheren Parametern
    # time_cost: Anzahl der Iterationen (höher = sicherer aber langsamer)
    # memory_cost: Speichernutzung in KiB (höher = sicherer aber speicherintensiver)
    # parallelism: Anzahl der parallelen Threads
    # hash_len: Länge des Ausgabe-Hashes in Bytes
    # salt_len: Länge des zufälligen Salts in Bytes
    argon2_hasher = argon2.PasswordHasher(
        time_cost=3,           # Standardwert für gute Balance
        memory_cost=65536,     # 64 MiB - guter Wert für moderne Systeme
        parallelism=4,         # 4 parallele Threads
        hash_len=32,           # 32 Bytes = 256 Bit
        salt_len=16            # 16 Bytes Salt
    )
    
    # Passwort mit Argon2 hashen
    # Argon2 ist ein moderner, speicherharter Passwort-Hashing-Algorithmus
    # der gegen GPU-basierte Angriffe und Rainbow-Tables resistent ist
    password_hash = argon2_hasher.hash(password)
    
    return password_hash