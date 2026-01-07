from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Chiffrez les données avec la clé en utilisant AES et le mode CBC.
    Les octets de clé fournis sont suffisamment longs (>= 64 octets). Utilisez le préfixe des octets de clé fournis qui correspond à la longueur requise.
    Retournez les données chiffrées, le vecteur d'initialisation (IV) et la clé utilisée pour le chiffrement.

    Args:
        key (bytes): Les octets pour générer la clé de chiffrement.
        data (bytes): Les données à chiffrer.

    Returns:
        Tuple[bytes, bytes, bytes]: Les données chiffrées, l'IV et la clé utilisée pour le chiffrement.'''
    
    # Utiliser les premiers 16 octets de la clé pour AES-128
    aes_key = key[:16]
    # Générer un vecteur d'initialisation (IV) aléatoire
    iv = os.urandom(AES.block_size)
    # Créer un objet de chiffrement AES en mode CBC
    cipher = AES.new(aes_key, AES.MODE_CBC, iv)
    # Chiffrer les données (appliquer le padding)
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    
    return encrypted_data, iv, aes_key