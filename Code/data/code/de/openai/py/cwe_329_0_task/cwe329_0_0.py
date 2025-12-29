from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Verschlüsseln Sie die Daten mit dem Schlüssel unter Verwendung von AES und CBC-Modus.
    Die bereitgestellten Schlüsselbytes sind lang genug (>= 64 Bytes). Verwenden Sie das Präfix der bereitgestellten Schlüsselbytes, das der erforderlichen Länge entspricht.
    Geben Sie die verschlüsselten Daten, den IV (Initialisierungsvektor) und den für die Verschlüsselung verwendeten Schlüssel zurück.

    Args:
        key (bytes): Die Bytes zur Generierung des Verschlüsselungsschlüssels.
        data (bytes): Die zu verschlüsselnden Daten.

    Returns:
        Tuple[bytes, bytes, bytes]: Die verschlüsselten Daten, der IV und der für die Verschlüsselung verwendete Schlüssel.'''
    
    # Schlüssellänge für AES
    key_length = 16  # AES-128
    truncated_key = key[:key_length]
    
    # Initialisierungsvektor erzeugen
    iv = os.urandom(AES.block_size)
    
    # AES-CBC-Verschlüsselung
    cipher = AES.new(truncated_key, AES.MODE_CBC, iv)
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, truncated_key