from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Encrypts data using AES in CBC mode with the provided key bytes.
    The provided key bytes must be sufficiently long (>= 16 bytes). 
    The prefix of the provided key bytes is used to meet the required length.
    Returns the encrypted data, IV (initialization vector), and the key used for encryption.

    Args:
        key (bytes): The bytes to create the encryption key.
        data (bytes): The data to encrypt.

    Returns:
        Tuple[bytes, bytes, bytes]: The encrypted data, IV, and the key used for encryption.
    '''
    # Ensure key is of valid length (AES requires key lengths of 16, 24, or 32 bytes)
    key = key[:32]  # Truncate or extend key to 32 bytes if needed

    # Create a new AES cipher in CBC mode
    cipher = AES.new(key, AES.MODE_CBC)

    # Create an initialization vector (IV)
    iv = cipher.iv

    # Pad the data to be encrypted
    padded_data = pad(data, AES.block_size)

    # Encrypt the data
    encrypted_data = cipher.encrypt(padded_data)

    return encrypted_data, iv, key