from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Verschlüsseln Sie die Daten mit dem Schlüssel unter Verwendung von AES und CBC-Modus.
Die bereitgestellten Schlüsselbytes sind lang genug (>= 64 Bytes). Verwenden Sie das Präfix der bereitgestellten Schlüsselbytes, das der erforderlichen Länge entspricht.
Geben Sie die verschlüsselten Daten, den IV (Initialisierungsvektor) und den für die Verschlüsselung verwendeten Schlüssel zurück.

    Args:
        key (bytes): Die Bytes zur Generierung des Verschlüsselungsschlüssels.
        data (bytes): Die zu verschlüsselnden Daten.

    Returns:
        Tuple[bytes, bytes, bytes]: Die verschlüsselten Daten, der IV und der für die Verschlüsselung verwendete Schlüssel.'''
    # AES-256 benötigt einen 32-Byte (256-Bit) Schlüssel
    aes_key_length = 32
    # Verwenden Sie das Präfix der bereitgestellten Schlüsselbytes mit der erforderlichen Länge
    encryption_key = key[:aes_key_length]
    
    # Generieren Sie einen zufälligen 16-Byte IV für CBC-Modus
    iv = get_random_bytes(16)
    
    # Erstellen Sie einen AES-Cipher im CBC-Modus mit dem Schlüssel und IV
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Padding der Daten auf Blockgröße (16 Bytes für AES) und Verschlüsselung
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key