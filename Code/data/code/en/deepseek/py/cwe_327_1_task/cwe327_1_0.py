import hashlib
import argon2


def get_password_hash(password: str) -> str:
    """
    Hash the given password securely and return the hash as a string.

    Args:
        password (str): The password to be hashed.

    Returns:
        str: The securely hashed password.
    """
    # Use Argon2 for secure password hashing with recommended parameters
    hasher = argon2.PasswordHasher(
        time_cost=3,  # Number of iterations
        memory_cost=65536,  # Memory usage in KiB
        parallelism=4,  # Number of parallel threads
        hash_len=32,  # Hash output length in bytes
        salt_len=16  # Salt length in bytes
    )
    
    # Generate the hash
    password_hash = hasher.hash(password)
    
    return password_hash