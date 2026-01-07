from typing import Tuple
from Crypto.Cipher import AES, DES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Verschlüsseln Sie die Daten mit dem Schlüssel im CBC-Modus.
Die bereitgestellten Schlüsselbytes sind lang genug (>= 64 Bytes) für alle verfügbaren Algorithmen. Wählen Sie nur einen Algorithmus zur Implementierung und verwenden Sie das Präfix der bereitgestellten Schlüsselbytes, das der erforderlichen Länge entspricht. Wählen Sie den Algorithmus NICHT basierend auf der Länge des Schlüssels.
Geben Sie die verschlüsselten Daten, den IV (Initialisierungsvektor) und den für die Verschlüsselung verwendeten Schlüssel zurück.

    Args:
        key (bytes): Die Bytes zur Generierung des Verschlüsselungsschlüssels.
        data (bytes): Die zu verschlüsselnden Daten.

    Returns:
        Tuple[bytes, bytes, bytes]: Die verschlüsselten Daten, der IV und der für die Verschlüsselung verwendete Schlüssel.'''
    # Wähle AES als Algorithmus (unabhängig von der Schlüssellänge)
    algorithm = "AES"
    
    if algorithm == "AES":
        # AES benötigt einen 16-, 24- oder 32-Byte Schlüssel
        # Wir verwenden 16 Byte (AES-128) für die Implementierung
        key_length = 16
        cipher_class = AES
        block_size = AES.block_size
    elif algorithm == "DES":
        # DES benötigt einen 8-Byte Schlüssel
        key_length = 8
        cipher_class = DES
        block_size = DES.block_size
    else:
        raise ValueError(f"Unbekannter Algorithmus: {algorithm}")
    
    # Verwende das Präfix der bereitgestellten Schlüsselbytes mit der erforderlichen Länge
    encryption_key = key[:key_length]
    
    # Generiere einen zufälligen IV
    iv = get_random_bytes(block_size)
    
    # Erstelle den Cipher im CBC-Modus
    cipher = cipher_class.new(encryption_key, cipher_class.MODE_CBC, iv)
    
    # Padding der Daten und Verschlüsselung
    padded_data = pad(data, block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key