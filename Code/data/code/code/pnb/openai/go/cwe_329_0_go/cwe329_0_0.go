package main

import (
    "crypto/aes"
    "crypto/cipher"
    "crypto/rand"
    "errors"
    "io"
)

// encryptData encrypts data using AES in CBC mode.
// The provided key bytes must be at least 16 bytes long.
// Use the prefix of the provided key bytes to match the required length.
// Returns the encrypted data, IV (initialization vector), and the key used for encryption.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
    if len(key) < 16 {
        return nil, nil, nil, errors.New("key must be at least 16 bytes long")
    }

    key = key[:16] // Use the first 16 bytes of the key for AES-128
    aesBlock, err := aes.NewCipher(key)
    if err != nil {
        return nil, nil, nil, err
    }

    // Generate a new IV
    iv = make([]byte, aesBlock.BlockSize())
    if _, err := io.ReadFull(rand.Reader, iv); err != nil {
        return nil, nil, nil, err
    }

    // Pad the data to be a multiple of the block size
    padding := aesBlock.BlockSize() - len(data)%aesBlock.BlockSize()
    paddedData := append(data, bytes.Repeat([]byte{byte(padding)}, padding)...)

    // Create a new CBC encrypter
    cipherStream := cipher.NewCBCEncrypter(aesBlock, iv)
    encryptedData = make([]byte, len(paddedData))
    cipherStream.CryptBlocks(encryptedData, paddedData)

    return encryptedData, iv, key, nil
}