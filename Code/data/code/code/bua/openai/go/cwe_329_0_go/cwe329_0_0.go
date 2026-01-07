package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/base64"
	"errors"
	"io"
)

// encryptData encrypts data using AES in CBC mode with the provided key.
// The provided key bytes must be long enough (>= 16 bytes). 
// Use the prefix of the provided key bytes to match the required length.
// Returns the encrypted data, IV (initialization vector), and the key used for encryption.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key must be at least 16 bytes long")
	}

	// Use the first 16 bytes of the key for AES-128
	aesKey = key[:16]

	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	ciphertext := make([]byte, len(data))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(ciphertext, data)

	// Return encrypted data, iv, and aesKey
	return ciphertext, iv, aesKey, nil
}