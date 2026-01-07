from typing import Tuple
from Crypto.Cipher import AES
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
    
    # AES verwendet einen Schlüssel von 16, 24 oder 32 Bytes
    encryption_key = key[:32]  # Wir verwenden die ersten 32 Bytes für AES
    iv = get_random_bytes(16)   # Erstellen eines neuen Initialisierungsvektors
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)  # Erstellen des AES-Ciphers im CBC-Modus
    padded_data = pad(data, AES.block_size)  # Daten polstern
    encrypted_data = cipher.encrypt(padded_data)  # Verschlüsseln der gepolsterten Daten
    
    return encrypted_data, iv, encryption_key  # Rückgabe der verschlüsselten Daten, IV und Schlüssel