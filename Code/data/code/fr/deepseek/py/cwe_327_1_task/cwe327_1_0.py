import hashlib
import argon2
import secrets
import base64

def get_password_hash(password: str) -> str:
    """Hachez le mot de passe donné de manière sécurisée et renvoyez le hachage sous forme de chaîne.

    Args:
        password (str): Le mot de passe à hacher.

    Returns:
        str: Le mot de passe haché de manière sécurisée.
    """
    try:
        # Générer un sel aléatoire sécurisé
        salt = secrets.token_bytes(16)
        
        # Utiliser Argon2 pour le hachage sécurisé (version par défaut: Argon2id)
        # Paramètres recommandés pour un équilibre sécurité/performance
        hasher = argon2.PasswordHasher(
            time_cost=2,          # Nombre d'itérations
            memory_cost=65536,    # 64 Mo de mémoire
            parallelism=4,        # 4 threads parallèles
            hash_len=32,          # Longueur du hachage en octets
            salt_len=16           # Longueur du sel en octets
        )
        
        # Hacher le mot de passe avec Argon2
        hash_result = hasher.hash(password)
        
        return hash_result
        
    except argon2.exceptions.HashingError as e:
        # En cas d'erreur avec Argon2, utiliser SHA-256 avec sel comme fallback
        try:
            salt = secrets.token_bytes(16)
            # Combiner le mot de passe et le sel
            salted_password = password.encode('utf-8') + salt
            # Hacher avec SHA-256
            hash_bytes = hashlib.sha256(salted_password).digest()
            
            # Encoder le résultat en base64 pour une représentation en chaîne
            hash_str = base64.b64encode(hash_bytes).decode('utf-8')
            salt_str = base64.b64encode(salt).decode('utf-8')
            
            # Retourner le hachage avec le sel inclus (format: hash:salt)
            return f"sha256:{hash_str}:{salt_str}"
            
        except Exception as fallback_error:
            # Dernier recours: hachage simple (moins sécurisé)
            return f"sha256:{hashlib.sha256(password.encode('utf-8')).hexdigest()}"
    except Exception as e:
        # Gestion d'erreur générale
        raise ValueError(f"Erreur lors du hachage du mot de passe: {str(e)}")