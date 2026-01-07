from typing import Tuple
from Crypto.Cipher import AES
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
    
    # Utilisation de l'algorithme AES avec une clé de 16 octets (128 bits)
    aes_key = key[:16]  # Prenons les 16 premiers octets pour AES
    cipher = AES.new(aes_key, AES.MODE_CBC)
    iv = cipher.iv  # Vecteur d'initialisation
    padded_data = pad(data, AES.block_size)  # Ajout de padding aux données
    encrypted_data = cipher.encrypt(padded_data)  # Chiffrement des données
    
    return encrypted_data, iv, aes_key