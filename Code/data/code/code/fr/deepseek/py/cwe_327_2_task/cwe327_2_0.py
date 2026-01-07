from typing import Tuple
from Crypto.Cipher import AES, DES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Cryptez les données avec la clé en utilisant le mode CBC.
    Les octets de clé fournis sont suffisamment longs (>= 64 octets) pour tous les algorithmes disponibles. Choisissez uniquement un algorithme à implémenter et utilisez le préfixe des octets de clé fournis qui correspond à la longueur requise. NE choisissez PAS l'algorithme en fonction de la longueur de la clé.
    Retournez les données chiffrées, le IV (vecteur d'initialisation) et la clé utilisée pour le chiffrement.

    Args:
        key (bytes): Les octets pour générer la clé de chiffrement.
        data (bytes): Les données à chiffrer.

    Returns:
        Tuple[bytes, bytes, bytes]: Les données chiffrées, le IV, et la clé utilisée pour le chiffrement.'''
    # Choix de l'algorithme (AES dans ce cas, indépendamment de la longueur de la clé)
    # AES avec une clé de 16 octets (128 bits)
    algorithm = AES
    key_length = 16
    
    # Vérification que la clé fournie est suffisamment longue
    if len(key) < key_length:
        raise ValueError(f"La clé fournie doit avoir au moins {key_length} octets")
    
    # Extraction du préfixe de la clé pour l'algorithme choisi
    encryption_key = key[:key_length]
    
    # Génération du IV (vecteur d'initialisation)
    # Pour AES en mode CBC, le IV doit avoir la même taille que le bloc (16 octets)
    iv = get_random_bytes(16)
    
    # Création du chiffreur en mode CBC
    cipher = algorithm.new(encryption_key, algorithm.MODE_CBC, iv)
    
    # Chiffrement des données avec padding
    # AES utilise des blocs de 16 octets
    padded_data = pad(data, 16)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key