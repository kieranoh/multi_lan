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
    
    # Vérifier que la clé est suffisamment longue
    if len(key) < 64:
        raise ValueError("La clé doit avoir au moins 64 octets")
    
    # Utiliser les 32 premiers octets (256 bits) pour la clé AES
    # AES-256 nécessite 32 octets (256 bits)
    aes_key = key[:32]
    
    # Générer un IV aléatoire de 16 octets (128 bits) pour le mode CBC
    iv = os.urandom(16)
    
    # Créer le chiffreur AES en mode CBC
    cipher = AES.new(aes_key, AES.MODE_CBC, iv)
    
    # Remplir les données pour qu'elles soient multiples de la taille de bloc (16 octets)
    padded_data = pad(data, AES.block_size)
    
    # Chiffrer les données
    encrypted_data = cipher.encrypt(padded_data)
    
    # Retourner les données chiffrées, l'IV et la clé utilisée
    return encrypted_data, iv, aes_key