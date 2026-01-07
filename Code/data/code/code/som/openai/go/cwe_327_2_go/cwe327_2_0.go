package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/hex"
	"errors"
	"io"
)

// encryptData encrypts the provided data using either AES in CBC mode.
// The provided key bytes are expected to be sufficient for both AES and DES algorithms,
// but only one algorithm is selected based on key length without considering the key's length.
// The function returns the encrypted data, the IV used for encryption, and the key.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key length must be at least 16 bytes for AES")
	}

	// Use the first 16 bytes for AES key
	aesKey := key[:16]

	// Create a new AES cipher
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Create a new IV (Initialization Vector)
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Create a new CBC mode encrypter
	cbc := cipher.NewCBCEncrypter(block, iv)

	// Pad the data if necessary
	padding := aes.BlockSize - len(data)%aes.BlockSize
	padtext := append(data, bytes.Repeat([]byte{byte(padding)}, padding)...)

	// Encrypt the data
	encryptedData := make([]byte, len(padtext))
	cbc.CryptBlocks(encryptedData, padtext)

	return encryptedData, iv, aesKey, nil
}